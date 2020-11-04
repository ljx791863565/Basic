#ifndef __ERR_H__
#define __ERR_H__

//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <errno.h>
//#include <netdb.h>  //gai_strerror()

//error-handling functions
void unix_error(char *msg);

void posix_error(int code, char *msg);

void dns_error(char *msg);

void gai_error(int code, char *msg);

void app_error(char *msg);


#endif
