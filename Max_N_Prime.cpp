#include <stdio.h>
#include <iostream>

int max_of_prime(int n)
{
	int i = 0;
	for (i = n-1; i > 1 ; i--) {
		bool flag = false;
		for (int j = i/2; j > 1; j--) {
			if (i%j == 0)  {
				flag = true;
				break;
			}
		}
		if (!flag)  {
			return i;
		}
	}
}

int main(int argc, const char *argv[])
{
	printf("the max of %d prime is %d\n", 100, max_of_prime(100));
	return 0;
}
