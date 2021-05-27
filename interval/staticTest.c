#include <stdio.h>

void func()
{
	static int a;
	printf("%d\n", a);
	a++;
	printf("%d\n", a);
}

int main(int argc, const char *argv[])
{
	func();
	func();
	return 0;
}
