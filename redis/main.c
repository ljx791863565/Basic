#include "zmalloc.h"

int main()
{
	char *ptr =zmalloc(100);
	zfree(ptr);

	return 0;
}
