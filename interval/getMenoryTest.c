#include <stdio.h>
#include <stdlib.h>

char *getMemnory(void)
{
	char *p = "hello world";
	return p;
}

int main(int argc, const char *argv[])
{
	char *str = getMemnory();
	printf("%s\n", str);

	return 0;
}
