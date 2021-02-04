#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len)
{
	size_t i;
	for (i=0; i<len; i++) {
		printf(" %.2x", start[i]);
	}
	printf("\n");
}

void show_int(int x)
{
	show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x)
{
	show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x)
{
	show_bytes((byte_pointer)&x, sizeof(void *));
}

void test_show_bytes(int val)
{
	int ival = val;
	float fval = (float)val;
	int *pval = &val;

	show_int(ival);

	show_float(fval);

	show_pointer(pval);
}

int main(int argc, const char *argv[])
{
	int i = 12345;
	test_show_bytes(i);\

	int val = 0x87654321;
	byte_pointer pval = (byte_pointer)&val;

	show_bytes(pval, 1);
	show_bytes(pval, 2);
	show_bytes(pval, 3);
	show_bytes(pval, 4);

	const char *p = "abcdef";
	show_bytes((byte_pointer)p, strlen(p));
	return 0;
}
