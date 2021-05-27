#include "../include/sum.h"
#include "../include/val.h"

int sum(int *x, int *y)
{
	val(x);
	puts("this is sum method");
	return (*x)+(*y);
}
