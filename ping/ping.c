
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <sys/time.h>

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <netdb.h>

#define K 1024
#define BUFSIZE 72
#define PACKET_NUM 128
typedef struct ping_packet {
	struct timeval tv_begin;
	struct timeval tv_end;
	short seq;		//序列号
	int flag;		//标示位 1 已经发送包但没有收到回应 0已经发送包并且接收到回应
}ping_packet;
static char dest_str[80];
static ping_packet pingpacket[PACKET_NUM];
static int rawsockfd;
static pid_t pid;
static struct sockaddr_in destAddr;
static int alive = 0;	//接收到线程退出信号 0 已经接收到 1 未接收到
static struct timeval tv_begin, tv_end, tv_interval;	//全局记录开始时间 结束时间和总时间
static short packet_send = 0;	//发送的数据包数
static short packet_recv = 0;	//接收的数据包数
static unsigned char send_buf[BUFSIZE];
static unsigned char recv_buf[2 *K];

static ping_packet *icmp_findpacket(int seq);
static unsigned short icmp_cksum(unsigned char *data, int len);
static struct timeval icmp_tvsub(struct timeval end, struct timeval begin);
static void icmp_statistics();
static void icmp_pack(struct icmp *icmph, int seq, struct timeval *tv, int length);
static int icmp_unpack(char *buf, int len);
static void *icmp_recv(void *argv);
static void *icmp_send(void *argv);
static void icmp_sigint(int signo);
static void icmp_usage();

static void icmp_usage()
{
	printf("ping IP\n");
}

static struct timeval icmp_tvsub(struct timeval end, struct timeval begin)
{
	struct timeval tv;
	tv.tv_sec = end.tv_sec - begin.tv_sec;
	tv.tv_usec = end.tv_usec - begin.tv_usec;
	if (tv.tv_usec < 0) {
		tv.tv_sec--;
		tv.tv_usec += 1000000;	//1s = 1000000us
	}
	return tv;
}

//信号函数
//当接收到信号时 设置多线程退出标志 记录时间
static void icmp_sigint(int signo)
{
	alive = 0;
	gettimeofday(&tv_end, NULL);
	tv_interval = icmp_tvsub(tv_end, tv_begin);

	return;
}

/*
 * 根据seq查找对应的数据包 
 * seq=-1时表示空包 此时找到flag=0标示位的包即已经得到回复的包返回 如果找不到返回NULL
 */
static ping_packet *icmp_findpacket(int seq)
{
	int i = 0;
	ping_packet *found = NULL;
	if (seq == -1) {
		for (i = 0; i < PACKET_NUM; i++) {
			if (pingpacket[i].flag == 0) {
				found = &pingpacket[i];
				break;
			}
		}
	}else if (seq >= 0) {
		for (i = 0; i < PACKET_NUM; i++) {
			if (pingpacket[i].seq == seq) {
				found = &pingpacket[i];
			}
		}
	}
	return found;
}

/*
 * 校验函数
 * TCP/IP协议栈使用的校验算法 
 * 对16位的数据进行累加 返回16位结果
 * data 数据 len 数据长度
 */
static unsigned short icmp_cksum(unsigned char *data, int len)
{
	int sum = 0;
	//len=0 偶数 len=1 奇数
	int odd = len & 0x01;	
	//以0xFFFE来保证数据的每一位都可以被累加到
	while (len & 0xfffe) {
		sum += *(unsigned short *)data;
		data += 2;
		len -= 2;
	}

	if (odd != 0) {
		unsigned short tmp = (*(data) << 8) &0xff00;
		sum += tmp;
	}

	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);

	return ~sum;
}

/*
 * 校验TCP头部 
 * 打包ICMP头部包并填充data数据 
 *
 * 参数：	icmph	保存ICMP头部信息的结构
 *			length	发送数据包长度 
 */
static void icmp_pack(struct icmp *icmph, int seq, struct timeval *tv, int length)
{
	unsigned char i = 0;
	//icmp_type = ICMP_ECHO && icmp_code = 0 时 请求会送报文
	//icmp_type = ICMP_ECHOREPLY && icmp_code = 0 时 请求回应报文
	icmph->icmp_type = ICMP_ECHO;
	icmph->icmp_code = 0;
	icmph->icmp_cksum = 0;
	icmph->icmp_seq = seq;
	icmph->icmp_id = pid & 0xffff;
	//填充数据
	for (i = 0; i < length; i++) {
		icmph->icmp_data[i] = i;
	}
	//利用特殊的校验算法为每一个数据都生成一个唯一校验值
	icmph->icmp_cksum = icmp_cksum((unsigned char*)icmph, length);
}

//统计返回结果 并打印
static void icmp_statistics()
{
	long time = (tv_interval.tv_sec *1000) + (tv_interval.tv_usec /1000);
	printf("--- %s ping statistics ---\n", dest_str);
	printf("%u packets transmitted, %u receved, %d%c packets lost, time %ld ms\n",
			packet_send, packet_recv, (packet_send - packet_recv)/packet_send*100, '%', time);
}

//解包icmp数据并打印在终端
static int icmp_unpack(char *buf, int len)
{
	int i, iphdrlen;
	struct ip *ip = NULL;
	struct icmp *icmp = NULL;
	int rtt;
	ip = (struct ip*)buf;
	//ip包头长度 单位32bit 即4字节 所以要*4 
	//一个IP包头的长度最长为“1111”，即15*4＝60个字节。IP包头最小长度为20字节
	iphdrlen = ip->ip_hl *4;	
	icmp = (struct icmp*)(buf + iphdrlen);
	len -= iphdrlen;
	if (len < 8) {
		printf("ICMP packet\'s length is less then 8\n");
		return -1;
	}

	if ((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid)) {
		struct timeval tv_interval, tv_recv, tv_send;
		ping_packet *packet = icmp_findpacket(icmp->icmp_seq);
		if (packet == NULL) {
			return -1;
		}
		//解压此包并设置该包的标示位为已经收到回应
		packet->flag = 0;
		tv_send = packet->tv_begin;
		gettimeofday(&tv_recv, NULL);
		tv_interval = icmp_tvsub(tv_recv, tv_send);
		rtt = tv_interval.tv_sec *1000 + tv_interval.tv_usec / 1000;

		printf("%d bytes from %s: icmp_seq=%d ttl=%d rtt=%d ms\n", 
				len, inet_ntoa(ip->ip_src), icmp->icmp_seq, ip->ip_ttl, rtt);
		packet_recv ++;
	}else {
		return -1;
	}
}

//发送报文线程
void *icmp_send(void *arg)
{
	
	gettimeofday(&tv_begin, NULL);
	while (alive) {
		int size = 0;
//		printf("this is the icmp_send\n");
		struct timeval tv;
		gettimeofday(&tv, NULL);
		//这里设置查找seq为-1即表示为空包
		ping_packet *packet = icmp_findpacket(-1);
		if (packet != NULL) {
			//第一次发送的数据包序号为0
			packet->seq = packet_send;
			//发包时设置此包为已经发送并未得到回应
			packet->flag = 1;
			gettimeofday(&packet->tv_begin, NULL);
		}
		icmp_pack((struct icmp*)send_buf, packet_send, &tv, 64);
		//向目标地址发送数据包 数据包大小64bytes
		size = sendto(rawsockfd, send_buf, 64, 0, (struct sockaddr *)&destAddr, sizeof(destAddr));
		if (size < 0) {
			perror("sendto()");
			continue;
		}
		//每次发送数据包后将序号+1
		packet_send++;
		sleep(1);
	}
	
}

//接收报文线程
void *icmp_recv(void *arg)
{
	//设置轮询时间
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 200;
	//long类型数组 用于保存套接字
	fd_set readfd;	
	while (alive) {
//		printf("this is the icmp_recv\n");
		int ret = 0;
		FD_ZERO(&readfd);	//清零readfd数组
		FD_SET(rawsockfd, &readfd);	//将rawsockfd加入readfd数组
		ret = select(rawsockfd+1, &readfd, NULL, NULL, &tv);
		int size = 0;
		switch (ret)
		{
			case -1:
				break;	//错误
			case 0:
				break;	//超时
			default:
				/*
				 * recv先等待 SOCKET s 的发送缓冲中的数据被协议传送完毕，如果协议在传送s的发送缓冲中的数据时出现网络错误，
				 * 那么recv函数返回SOCKET_ERROR；
				 *
				 * 如果s的发送缓冲区中没有数据或者数据被协议成功发送完毕后，recv先检查套接字s的接收缓冲区；
				 * 
				 * 如果s的接收缓冲区中没有数据或者协议正在接收数据，那么recv就一直等待，直到协议把数据接收完毕；
				 * 
				 * 当协议把数据接收完毕，recv函数就把s的接收缓冲区中的数据copy到buf中。
				 * （注意协议接收到的数据可能大于buf的长度，所以 在这种情况下要调用几次recv函数才能把s的接收缓冲中的数据copy完。
				 *  recv函数仅仅是copy数据，真正的接收数据是协议来完成的）， 
				 * recv函数返回其实际copy的字节数。如果recv在copy时出错，那么它返回SOCKET_ERROR；
				 * 
				 * 默认 socket 是阻塞的，阻塞与非阻塞recv返回值没有区分，都是 <0 出错 =0 连接关闭 >0 接收到数据大小。
				 *
				 * 如果recv函数在等待协议接收数据时网络中断了，那么它返回0
				 *
				 * 成功执行时，返回接收到的字节数。
				 * 另一端已关闭则返回0。
				 * 失败返回-1，errno被设为以下的某个值 
				 *
				 * 返回值<0时并且(errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)的情况下认为连接是正常的，继续接收
				 */
				size = recv(rawsockfd, recv_buf, sizeof(recv_buf), 0);
				// 指操作被中断唤醒，需要重新读/写 如果出现EINTR即errno为4，错误描述Interrupted system call，操作应该继续
				if (errno == EINTR) {
					perror("recv()");
					continue;
				}
				ret = icmp_unpack(recv_buf, size);
				if (ret == 1) {
					continue;
				}
				break;
		}
	}
}
int main(int argc, const char *argv[])
{
	//usage: ./ping ip 
//	if (argc < 2) {
//		icmp_usage();
//		return -1;	
//	}
	struct protoent *protocol = NULL;
	char protoname[BUFSIZE] = "icmp";
	protocol = getprotobyname(protoname);
	if (protocol == NULL) {
		perror("getprotobyname()");
		return -1;
	}

	memcpy(dest_str, argv[1], strlen(argv[1]+1));
	memset(pingpacket, 0, (sizeof(struct ping_packet) * PACKET_NUM));

	rawsockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto);
	if (rawsockfd < 0) {
		perror("socket()");
		return -1;
	}

	pid = getpid();

	int size = PACKET_NUM * K;
	//设置tcp接收缓冲区的容量上限
	setsockopt(rawsockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));

	memset(&destAddr, 0, sizeof(destAddr));
	unsigned long inaddr = 1;
	destAddr.sin_family = AF_INET;

	inaddr = inet_addr(argv[1]);
	struct hostent *host = NULL;
	//表示为无效地址
	if (inaddr == INADDR_NONE) {
		host = gethostbyname(argv[1])	;
		if (host == NULL) {
			perror("gethostbyname()");
			return -1;
		}
		memcpy((char*)&destAddr.sin_addr, host->h_addr, host->h_length);
	}else {
		memcpy((char*)&destAddr.sin_addr, &inaddr, sizeof(inaddr));
	}
	inaddr = destAddr.sin_addr.s_addr;
	// 56(84)
	// 指定每次ping发送的数据字节数，默认为“56字节”+“28字节”的ICMP头，一共是84字节；
	// 包头+内容不能大于65535，所以最大值为65507（linux:65507, windows:65500）；
	printf("PING %s (%ld.%ld.%ld.%ld) 56(84) bytes of data.\n",dest_str, 
			(inaddr&0x000000ff)>>0, (inaddr&0x0000ff00)>>8, (inaddr&0x00ff0000)>>16, (inaddr&0xff000000)>>24);

	signal(SIGINT, icmp_sigint);

	alive = 1;
	pthread_t send_thread, recv_thread;
	int ret = pthread_create(&send_thread, NULL, icmp_send, NULL);
	if (ret < 0) {
		perror("pthread_create() icmp_send");
		return -1;
	}
	ret = pthread_create(&recv_thread, NULL, icmp_recv, NULL);
	if (ret < 0) {
		perror("pthread_create() icmp_recv");
		return -1;
	}

	pthread_join(send_thread, NULL);
	pthread_join(recv_thread, NULL);

	close(rawsockfd);
	icmp_statistics();
	return 0;
}
