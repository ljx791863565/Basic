#include <limits.h>
#include <stdio.h>

int main()
{
	printf("signed char min = %d signed char max = %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char max= %u\n", UCHAR_MAX);
	printf("signed short min = %d signed short max = %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short max = %d\n", USHRT_MAX);
	printf("signed int min = %d signed int max = %d\n", INT_MIN, INT_MAX);
	printf("unsigned int max = %u\n", UINT_MAX);
	printf("signed long min = %ld signed long max = %ld\n", LONG_MIN, LONG_MAX);
	printf("unsigned long max = %lu\n", ULONG_MAX);
	printf("signed long long min = %lld signed long long max = %lld\n", LLONG_MIN, LLONG_MAX);
	printf("unsigned long long max = %llu\n", ULLONG_MAX);

	return 0;
}
