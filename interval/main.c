#include <stdio.h>
#include "test.h"

int main(int argc, const char *argv[])
{
	Boolean a;
	printf("%d\n", a);


	printf("%d\n", 129 % 32);
	printf("%d\n", 129 - (129 >> 5 << 5));
	return 0;
}
