#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "rio.h"

#define SA struct sockaddr

int main(void)
{
    int listenfd, connfd;
    socklen_t clilen;
    struct sockaddr_in servaddr ,cliaddr;
    int ret;
    rio_t rio;
    char buffer[2048];

    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) <= 0)
    {
        perror("SOCKET");
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(4321);

    if((ret = bind(listenfd, (SA *)&servaddr, sizeof(servaddr))) < 0)
    {
        perror("BIND");
        return -1;
    }

    if((ret = listen(listenfd, 24)) < 0)
    {
        perror("LISTEN");
        return -1;
    }

    for(;;)
    {
        clilen = sizeof(cliaddr);
        if((connfd = accept(listenfd, (SA *)&cliaddr, &clilen)) < 0)
        {
            perror("ACCEPT");
            return -1;
        }
        rio_readinitb(&rio, connfd);
        while((ret = rio_readlineb(&rio, buffer, sizeof(buffer))) > 0)
            rio_writen(connfd, buffer, ret);
    }
    return 0;
}
