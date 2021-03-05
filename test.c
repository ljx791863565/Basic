#include <stdio.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, const char *argv[])
{
	int sn_len;
	sn_len = strlen(argv[1]);
	if (sn_len != 16)  {
		printf("sn lengths is %d, sn length must be 16.\n", sn_len);
	}else {
		printf("SN: [%s]\n", argv[1]);
	}

	int sn[16] = {0};

	int i;
	for (i = 0; i < 16; i++) {
	
		sn[i] = toascii(argv[1][i]);
	}
	
	for(i=0; i < 16; i++)
		printf("%d", sn[i]);
	printf("\n");
	return 0;
}
