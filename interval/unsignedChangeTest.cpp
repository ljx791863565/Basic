#include <iostream>
#include <stdio.h>

int main(int argc, const char *argv[])
{
	short s = -12345;
	unsigned u = s;
	printf("%u\n", u);

	unsigned u1 = (unsigned)(int)s;
	printf("%u\n", u1);

	unsigned u2 = (unsigned)(unsigned short)s;
	printf("%u\n", u2);
	return 0;
}
