#include "include/common.h"

int main(int argc, const char *argv[])
{
	puts("当前线程sleep 2秒");
	sleep(2);
	int x = 10;
	int y = 20;
	int z = sum(&x, &y);
	puts("this is main");
	printf("Z:%d\n", z);
	x = 20;
	z = get(&x, &y);
	printf("Z:%d\n", z);

	return 0;
}
