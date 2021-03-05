#include <stdio.h>
#include <stdlib.h>

void display()
{
	system("clear");
	printf("  *** U-Boot Boot Menu ***\n");
	printf("\n");
	printf("\t1. Stratup system (Default)\n");
	printf("\t2. upgrade firmware\n");
	printf("\t3. upgrade bootloader\n");
	printf("\n");
	printf("  press UP/DOWN to move, ENTER ro select\n");
}

int main(int argc, const char *argv[])
{

	display();	
	int ch = 0;
	while ((ch = getchar()) != EOF) {
		
	}
	return 0;
}
