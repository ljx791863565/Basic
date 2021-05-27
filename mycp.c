#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, const char *argv[])
{
	int fdto, fdfrom;

	fdfrom = open("../art.bin", O_RDWR);
	fdto = open("../art_20.bin", O_RDWR | O_TRUNC |O_CREAT, 0664);

	char buf[1024];
	while () {
	
	}
	return 0;
}
