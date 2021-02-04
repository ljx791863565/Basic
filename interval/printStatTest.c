#include <stdio.h>

int main(int argc, const char *argv[])
{
	int n = 10;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n/2 -i; j++) {
			printf(" ");
		}
		for (int k = 0; k < i; k++) {
			printf("*");
		}
		printf("\n");
	}
	return 0;
}
