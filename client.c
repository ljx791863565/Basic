#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define MAX_BUF 1024

int main(int argc, const char *argv[])
{
	if (argc != 2)  {
		printf("usage: client [addr] [port]\n");
	}

	struct sockaddr_in serAddr;
	memset(&serAddr, 0, sizeof(serAddr));

	serAddr.sin_family = AF_INET;
	serAddr.sin_addr.s_addr = inet_addr(argv[1]);
	serAddr.sin_port = htons(argv[2]);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)  {
		perror("socket");
		return -1;
	}

	int ret = connect(sockfd, (struct sockaddr*)&serAddr, sizeof(serAddr));
	if (ret < 0)  {
		perror("connect");
		return -1;
	}


	return 0;
}

