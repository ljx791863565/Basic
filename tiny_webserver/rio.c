#include "rio.h"
/*
 * 从fd中读取n个字节到buf 返回读取的字节数 出错时返回-1
 * 实现中使用了nleft变量来循环读取 直到读取到nletf为0或者无数据可读取时返回
 * 当遇到信号中断而产生的EINTR时做处理
 */
ssize_t rio_readn(int fd, void *buf, size_t n)
{
	ssize_t nread;
	ssize_t nleft = n;
	char *bp = (char *)buf;

	while (nleft > 0) {
		if ((nread = read(fd, bp, nleft)) < 0) {
			//此时错误值表示由于信号中断 read没有读取到任何数据
			if (errno == EINTR) {
				nread = 0;
			}else {
				return -1;
			}
		}
		//此时一个字节都没有读取到 跳出循环
		else if (nread == 0){
			break;
		}
		nleft -= nread;
		bp += nread;
	}
	return  (n - nleft);
}

/*
 * 向fd中写入n个字节
 */
ssize_t rio_writen(int fd, void *buf, size_t n)
{
	ssize_t nwritten;
	size_t nleft = n;
	char *bp = (char *)buf;

	while (nleft > 0) {
		if ((nwritten = write(fd, bp, nleft)) <= 0) {
			if (errno == EINTR) {
				nwritten = 0;
			}else {
				return -1;
			}
		}
		nleft -= nwritten;
		bp += nwritten;
	}
	return n;
}

/*
 * init rio_t
 */
void rio_readinitb(rio_t *rp, int fd)
{
	rp->rio_fd = fd;
	rp->rio_cnt = 0;
	rp->rio_bufptr = rp->rio_buf;
}

/*
 * 此函数首先检查缓冲区是否为空，若为空，则调用read从fd中读取最数量非的数据填充缓冲区。
 * 若不为空则从缓冲区中取出n个字节。若缓冲区中剩余字节数不足n，则将缓冲区中全部取出，并返回读取到的字节数。
 */
static ssize_t rio_read(rio_t *rp, void *buf, size_t n)
{
	ssize_t cnt;
	while (rp->rio_cnt <= 0) {
		rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
		if (rp->rio_cnt < 0) {
			if (errno != EINTR) {
				return -1;
			}
		}else if (rp->rio_cnt == 0) {
			return 0;
		}else {
			rp->rio_bufptr = rp->rio_buf;
		}
	}
	cnt = n;
	if (rp->rio_cnt < n) {
		cnt = rp->rio_cnt;
	}
	memcpy(buf, rp->rio_bufptr, cnt);
	rp->rio_cnt -= cnt;
	rp->rio_bufptr += cnt;
	return cnt;
}
/*
 * readline的rio版本 调用了rio_read填写缓冲区 
 * 带缓冲的读取一行，返回字节数包括换行符。
 */
ssize_t rio_readlineb(rio_t *rp, void *buf, size_t n)
{
	size_t i, ret;
	char c;
	char *bp = (char *)buf;
	for (i = 0; i < n; i++) {
		if ((ret = rio_read(rp, &c, 1)) == 1) {
			*bp++ = c;
			if (c == '\n') {
				break;
			}
		}else if (ret == 0) {
			if (i == 1){
				return 0;
			}else {
				break;
			}
		}else {
			return -1;
		}
	}
	*bp = '\0';
	return i;
}

/*
 * 此函数类似rio_readn,不过因为加入了缓冲区，所以减少了陷入内核态时的开销。
 */
ssize_t rio_readnb(rio_t *rp, void *buf, size_t n)
{
	ssize_t nread;
	size_t nleft = n;
	char *bp = (char *)buf;

	while (nleft > 0) {
		if ((nread = rio_read(rp, bp, nleft)) < 0) {
			if (errno == EINTR) {
				nread = 0;
			}else {
				return -1;
			}
		}else if (nread == 0) {
			break;
		}
		nleft -= nread;
		bp += nread;
	}
	return (n - nleft);
}

ssize_t Rio_readn(int fd, void *ptr, size_t n)
{
	ssize_t rc;
	if ((rc = rio_readn(fd, ptr, n)) < 0) {
		unix_error("rio_readn errpr");
	}
	return rc;
}

void Rio_writen(int fd, void *usrbuf, size_t n)
{
	if (rio_writen(fd, usrbuf, n) != n) {
		unix_error("rio_writen error");
	}
}

void Rio_readinitb(rio_t *pr, int fd)
{
	rio_readinitb(pr, fd);
}

ssize_t Rio_readnb(rio_t *pr, void *usrbuf, size_t n)
{
	ssize_t rc;
	if ((rc = rio_readnb(pr, usrbuf, n)) < 0) {
		unix_error("rio_readnb error");
	}
	return rc;
}

ssize_t Rio_readlineb(rio_t *pr, void *usrbuf, size_t maxlen)
{
	ssize_t rc;
	if ((rc = rio_readlineb(pr, usrbuf, maxlen)) <0) {
		unix_error("readlineb error");
	}
	return rc;
}

