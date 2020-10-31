#ifndef __RIO_H__
#define __RIO_H__
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define RIO_BUFSIZE 8192

typedef struct sockaddr SA;

/*
 * Rio包即为Robust io函数包。包中函数是对Linux基本I/O函数的封装，使其更加健壮、高效，更适用于网络编程。
 *
 * ## 字节流套接字上的read和write函数所表现的行为不同于通常的文件IO。
 * ## 字节流套接字上调用read或write输入或输出的字节数可能比请求的数量少，然而这不是出错的状态。
 * ## 这个现象的原因在于内核中用于套接字的缓冲区可能已经到达了极限。此时所需的是调用者再次调用read或write函数，以输入或输出剩余的字节。
 *
 * ## 如果进程在一个慢系统调用(slow system call)中阻塞时，当捕获到某个信号且相应信号处理函数返回时，
 * ## 这个系统调用被中断，调用返回错误，设置errno为EINTR（相应的错误描述为“Interrupted system call”）。
 *
 * 以上两点表明，在网络编程中，你虽然调用read/write读/写了n个字符，但实际读写的数量可能比请求的数量少。
 *
 * rio_readn() 函数尝试从fd中读取n个字符到buf中，与read函数相比，它被信号处理函数中断后会再次尝试读取。
 * 因此，在除了可读字符数小于n情况下，该函数可以保证读取n个字节。
 *
 * rio_writen() 函数和rio_readn()函数一样可以保证写入n个字符到fd中
 *
 * rio_readlineb() 和 rio_readnb()两个带缓冲区的函数 缓冲区存在的目的是为了减少因多次调用系统级IO函数，陷入内核态而带来的额外开销
 */
typedef struct
{
	int rio_fd;						//Descriptor for this internal buf
	int rio_cnt;					//Unread bytes in internal buf
	char *rio_bufptr;				//Printer of next unread byte in internal buf
	char rio_buf[RIO_BUFSIZE];		// Internal buffer
}rio_t;

ssize_t rio_readn(int fd, void *buf, size_t n);
ssize_t rio_writen(int fd, void *buf, size_t n);
void rio_readinitb(rio_t *rp, int fd);
ssize_t rio_readlineb(rio_t *rp, void *buf, size_t n);
ssize_t rio_readnb(rio_t *rp, void *buf, size_t n);

#endif
