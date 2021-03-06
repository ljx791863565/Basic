#include "stack.h"
#define N 16

void conversion()
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	if (s == NULL) {
		perror("malloc");
		return;
	}
	InitStack(s);
	int num = 0;
	Elemtype e;
	printf("input a number\n");
	scanf("%d", &num);
	printf("the %d redix of %d is :", N, num);
	while (num) {
		Push(s, num % N);
		num /= N;
	}

	while (!StackEmpty(s)) {
		Pop(s, &e);
		if (e < 9) {
			printf("%d", e);
		}
		printf("%c", e);
	}
	printf("\n");

}
int main(int argc, const char *argv[])
{
	conversion();
	return 0;
}
