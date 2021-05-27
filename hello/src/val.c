#include "../include/val.h"

int val(int *x)
{
	struct event_base *base;
	base = event_base_new();
	const char *X = event_base_get_method(base);
	printf("method:%s\n", X);
	event_base_free(base);


	puts("this is value==");
	printf("X:%d\n", *x);

	return 0;
}
