#include <stdio.h>

struct test {
	unsigned short int a:5;
	unsigned short int b:5;
	unsigned short int c:6;
};

int main(int argc, const char *argv[])
{
	struct test t;
	t.a = 16;
	t.b = 4;
	t.c = 0;

	int i = *(short *)&t;
	printf("%d\n", i);
	return 0;
}
