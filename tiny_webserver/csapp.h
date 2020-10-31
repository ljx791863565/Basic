#ifndef __CSAPP__H__
#define __CSAPP__H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>
#include <dirent.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "rio.h"
// define mode rw_ rw_ rw_
#define DEF_MODE	S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH
// define mode mask ___ _w_ _w_
#define DRF_UMASK	S_IWGRP|S_IWOTH

extern int h_errno;
extern char **environ;

#define MAXLINE	8192
#define MAXBUF	8192
#define	LISTENQ 1024

//error-handling functions
void unix_error(char *msg);
void posix_error(int code, char *msg);
void dns_error(char *msg);
void gai_error(int code, char *msg);
void app_error(char *msg);

//process control wrappers
pid_t Fork();
void Execve(const char *filename, char *const argv[], char *const envp[]);
pid_t Wait(int *status);
pid_t Waitpid(pid_t pid, int *iptr, int options);
void Kill(pid_t pid, int signum);
unsigned int Sleep(unsigned int secs);
void Pause();
unsigned int Alarm(unsigned int secs);
void Setpgid(pid_t pid, pid_t gpid);
pid_t Getpgrp();

//signal wrappers
typedef void handler_t(int);
handler_t *signal(int signum, handler_t *handler);
void Sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
void Sigemptyset(sigset_t *set);
void Sigfillset(sigset_t *set);
void Sigaddset(sigset_t *set, int signum);
void Sigdelset(sigset_t *set, int signum);
int Sigismenber(const sigset_t *set, int signum);
int Sigsuspend(const sigset_t *set);

//sio signal-safe I/O 
ssize_t sio_puts(char s[]);
ssize_t sio_putl(long v);
void sio_error(char s[]);

//sio wrappers
ssize_t Sio_puts(char s[]);
ssize_t Sio_putl(long v);
void sio_error(char s[]);

//Unix I/O wrappers
int Open(const char *pathname, int flags, mode_t mode);
ssize_t Read(int fd, void *buf, size_t n);
ssize_t Write(int fd, void *buf, size_t n);
off_t Lseek(int fildes, off_t offset, int whence);
void Close(int fd);
int Select(int n, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);
int Dup2(int fd1, int fd2);
void Stat(const char *filename, struct stat *buf);
void Fstat(int fd, struct stat *buf);

//Directory wrappers
DIR *Opendir(const char *name);
struct dirent *Readdir(DIR *pdir);
int Closedir(DIR *pdir);

//Memory mapping wrappers
void *Mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);
void Munmap(void *start, size_t length);

//Standard I/O wrappers
FILE *Fdopen(int fd, const char *type);
void Fclose(FILE *fp);
FILE *Fopen(const char *filename, const char *mode);
void Fputs(const char *ptr, FILE *stream);
char *Fgets(char *ptr, int n, FILE *stream);
size_t Fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
void Fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);

//Dynamic storage allocation wrappers
void *Malloc(size_t size);
void *Realloc(void *ptr, size_t size);
void *Calloc(size_t nmemb, size_t size);
void Free(void *ptr);

//socket interface wrappers
int Socket(int domain, int type, int protocol);
void Setsockopt(int fd, int level, int optname, const void *optval, int optlen);
void Bind(int sockfd, struct sockaddr *addr, int addrlen);
void Listen(int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *addr, int addrlen);

//protocol independent wrappers
void Getaddrinfo(const char *node, const char *service, const struct addrinfo *hints, struct addrinfo **res);
void Getnameinfo(const struct sockaddr *sa, socklen_t salen, char *host, size_t hostlen, char *serv, size_t servlen, int flags);
void Freeaddrinfo(struct addrinfo *res);
void Inet_ntop(int af, const void *src, char *dst, socklen_t size);
void Inet_pton(int af, const char *src, void *dst);

//DNS wrappers
struct hostent *Gethostbyname(const char *name);
struct hostent *Gethostbyaddr(const char *addr, int len, int type);

//pthread thread control wrappers
void Pthread_create(pthread_t *pid, pthread_attr_t *pattr, void *(*handler)(void *), void *arg);
void Pthread_join(pthread_t pid, void **thread_return);
void Pthread_cancel(pthread_t pid);
void Pthread_detach(pthread_t pid);
void Pthread_exit(void *retval);
pthread_t Pthread_self(void);
void Pthread_once(pthread_once_t *once_control, void(*init_fanction)());

//wrappers for robust I/O routines
ssize_t Rio_readn(int fd, void *ptr, size_t n);
void Rio_writen(int fd, void *usrbuf, size_t n);
void Rio_readinitb(rio_t *pr, int fd);
ssize_t Rio_readnb(rio_t *pr, void *usrbuf, size_t n);
ssize_t Rio_readlineb(rio_t *pr, void *usrbuf, size_t maxlen);

//POSIX semaphore wrappers
void Sem_init(sem_t *sem, int pshared, unsigned int value);
void P(sem_t *sem);
void V(sem_t *sem);

//Reentrant protocol-independent client/server helpers
int open_clientfd(char *hostname, char *port);
int open_listenfd(const char *port);

//Reentrant protocol-independent client/server helpers wrappers
int Open_clientfd(char *hostname, char *port);
int Open_listenfd(const char *post);
#endif
