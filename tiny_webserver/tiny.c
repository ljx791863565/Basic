#include "csapp.h"
#include "rio.h"
#define HTMLNAME "home.html"

void get_filetype(char *filename, char *filetype)
{
	if (strstr(filename, ".html")) {
		strcpy(filetype, "text/html");
	}else if (strstr(filename, ".gif")){
		strcpy(filetype, "image/gif");
	}else if (strstr(filename, ".png")){
		strcpy(filetype, "image/png");
	}else if (strstr(filename, ".jpg")) {
		strcpy(filetype, "image/jepg");
	}else {
		strcpy(filetype, "text/plain");
	}
}

void serve_static(int fd, char *filename, int filesize)
{
	int srcfd;
	char *psrc, filetype[MAXLINE], buf[MAXLINE];

	get_filetype(filename, filetype);
	sprintf(buf, "HTTP/1.0 200 ok\r\n");
	sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
	sprintf(buf, "%sConnection: close\r\n", buf);
	sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
	sprintf(buf, "%sConetet-type: %s\r\n\r\n", buf, filetype);
	Rio_writen(fd, buf, strlen(buf));
	printf("Response headers:\n");
	printf("%s", buf);

	srcfd = Open(filename, O_RDONLY, 0);
	psrc = Mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
	Close(srcfd);
	Rio_writen(fd, psrc, filesize);
	Munmap(psrc, filesize);
}

void serve_dynamic(int fd, char *filename, char *cgiargs)
{
	char buf[MAXLINE], *emptylist[] = {NULL};
	sprintf(buf, "HTTP/1.0 200 ok\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Server: Tiny Web Server\r\n");
	Rio_writen(fd, buf, strlen(buf));

	if (Fork() == 0) {
		setenv("QUERY_STRING", cgiargs, 1);
		Dup2(fd, STDOUT_FILENO);
		Execve(filename, emptylist, environ);
	}
	Wait(NULL);
}

//http回复body封装 回复内容buf封装
void clienterror(int fd, char *cause, char *errnum, char *shortmsg, char *longmsg)
{
	char buf[MAXLINE], body[MAXLINE];
	sprintf(body, "<html><title>Tiny Error</title>");
	sprintf(body, "%s<body bgcolor=""ffffff"">\r\n",body);
	sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
	sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
	sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

	sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-type: text/html\r\n");
	Rio_writen(fd, buf, strlen(buf));
	sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
	Rio_writen(fd, buf, strlen(buf));
	Rio_writen(fd, body, strlen(body));
}

//解析获得的http uri
int parse_uri(char *uri, char *filename, char *cgiargs)
{
	char *ptr;
	//static html
	//uri为'/'
	if (!strstr(uri, "cgi-bin")) {
		strcpy(cgiargs, "");
		strcpy(filename, ".");
		strcat(filename, uri);
		if (uri[strlen(uri) -1] == '/') {
			strcat(filename, HTMLNAME);
		}
		return 1;
	}else {
		//char * index(const char *s, int c);
		//index()用来找出参数s 字符串中第一个出现的参数c 地址，然后将该字符出现的地址返回。字符串结束字符(NULL)也视为字符串一部分
		//返回值：如果找到指定的字符则返回该字符所在地址，否则返回0.
		ptr = index(uri, '?');
		if (ptr) {
			strcpy(cgiargs, ptr+1);
			*ptr = '\0';
		}else {
			strcpy(cgiargs, "");
		}
		strcpy(filename, ".");
		strcat(filename, uri);
		return 0;
	}
}

// 读取并打印http请求信息
void read_requesthdrs(rio_t *pr)
{
	char buf[MAXLINE];
	Rio_readlineb(pr, buf, MAXLINE);
	printf("(%s:%d) %s ", __FILE__, __LINE__, buf);
	//如果此时buf中没有\r\n结束符表示还有信息未读取完 继续调用readlineb()
	while (strcmp(buf, "\r\n")) {
		Rio_readlineb(pr, buf, MAXLINE);
		printf("(%s:%d) %s ", __FILE__, __LINE__, buf);
	}
	return ;
}

void doit(int fd)
{
	struct stat sbuf;
	int is_static;
	char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
	char filename[MAXLINE], cgiargs[MAXLINE];
	rio_t rio;

	//将请求读入到rio中
	Rio_readinitb(&rio, fd);
	if (!Rio_readlineb(&rio, buf, MAXLINE)) {
		return;
	}
	printf("(%s:%d) %s",__FILE__, __LINE__, buf);
	sscanf(buf, "%s %s %s", method, uri, version);
//	printf("method: %s uri: %s version: %s", method, uri, version);
	if (strcasecmp(method, "GET")) {
		clienterror(fd, method, "501", "Not Implemented", "Tiny does not implement this method");
		return;
	}
	read_requesthdrs(&rio);

	is_static = parse_uri(uri, filename,cgiargs);
	//can not get the filename stat info
	if (stat(filename, &sbuf) < 0) {
		clienterror(fd, filename, "404", "Not found", "Tiny couldn't find this file");
		return;
	}

	if (is_static) {
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Frobidden", "Tiny couldn't read the file");
			return;
		}
		serve_static(fd, filename, sbuf.st_size);
	}else {
		if (!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)) {
			clienterror(fd, filename, "403", "Forbidden", "Tiny couldn't run the CGI program");
			return;
		}
		serve_dynamic(fd, filename, cgiargs);
	}
}

int main(int argc, const char *argv[])
{
	int listenfd, connfd;
	char hostname[MAXLINE], port[MAXLINE];
	socklen_t clientlen;
	/*
	 * 通用结构体 128字节
	 *  #if ULONG_MAX > 0xffffffff
	 *  # define __ss_aligntype __uint64_t
	 *  #else
	 *  # define __ss_aligntype __uint32_t
	 *  #endif
	 *  #define _SS_SIZE        128
	 *  #define _SS_PADSIZE     (_SS_SIZE - (2 * sizeof (__ss_aligntype)))
	 *  struct sockaddr_storage
	 *  {
	 *  sa_family_t ss_family;      // Address family 
	 *  __ss_aligntype __ss_align;  // Force desired alignment.  
	 *  char __ss_padding[_SS_PADSIZE];
	 *  };
	 */
	
	struct sockaddr_storage clientaddr;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <port>\n", argv[0]);
		exit(0);
	}
	
	//通过传入port到getaddrinfo获得listenfd。 并且对此fd bing() listen()
	listenfd = Open_listenfd(argv[1]);

	while (1) {
		clientlen = sizeof(clientaddr);
		connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
		Getnameinfo((SA *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
		printf("Accepted connection from (%s, %s)\n", hostname, port);

		doit(connfd);
		Close(connfd);
	}
	return 0;
}
