#include "unp.h"

int Accept(int fd, struct sockaddr *sa, socklen_t *psalen)
{
	int n;
again:
	if ( (n = accept(fd, sa, psalen)) < 0) {
#ifdef EPROTO
		if (errno == EPROTO || errno == ECONNABORTED) 
#else 
		if (errno == ECONNABORTED) 
#endif
			goto again;
		else 
			err_sys("accept errno");
	}
	return (n);
}

int Socket(int family, int type, int protocol)
{
	int n;
	if ( (n = socket(fd, type, protocol)) < 0) {
		err_sys("Socket error");
	}
	return (n);
}

void Bind(int fd, const struct sockaddr *sa, socklen_t salen)
{
	if (bind(fd, sa, salen) < 0) {
		err_sys("bind error");
	}
}

void Connect(int fd, const char sockaddr *sa, socklen_t salen)
{
	if (connect(fd, sa, salen) < 0) {
		err_sys("connect error");
	}
}

void Listen(int fd, int backlog)
{
	char *ptr;
	if ( (ptr = getenv("LISTENQ")) != NULL) {
		backlog = atoi(ptr);
	}
	if (listen(fd, backlog) < 0) {
		err_sys("listen error");
	}
}

ssize_t Recv(int fd, void *ptr, size_t nbytes, int flags)
{
	ssize_t n;
	if ( (n = recv(fd, ptr, nbytes, flags)) < 0) {
		err_sys("recv error");
	}
	return n;
}

void Send(int fd, void *ptr, size_t nbytes, int flags)
{
	if (send(fd, ptr, nbytes, flags) != (ssize_t)nbytes) {
		err_sys("send error");
	}
}


