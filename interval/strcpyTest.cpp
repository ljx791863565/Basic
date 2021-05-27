#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

int main(int argc, const char *argv[])
{
	char msg[100] = "Hello World";

	char temp[100] {0};

	printf("%s", msg);
	printf("%lu %zu\n", sizeof(msg), strlen(msg));
	strncpy(temp, msg, 8);
	printf("$$$$$$$$$$$$$$$$\n");
	printf("%s", temp);
	printf("%lu %zu\n", sizeof(temp), strlen(temp));
	return 0;
}
