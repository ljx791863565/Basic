#include "../basic.h"
#include "stack.h"

FILE *fp;

Status copy(Elemtype e)
{
	fputc(e, fp);
	return OK;
}

void LineEdit()
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	int ch, c;
	InitStack(s);
	printf("input a file\n");
	ch = getchar();
	while (ch != EOF) {
		while (ch != EOF && ch != '\n') {
			switch (ch)
			{
				case '#':
					Pop(s, &ch);
					break;
				case '@':
					ClearStack(s);
					break;
				default:
					Push(s, ch);
			}
			ch = getchar();
		}
		StackTraverse(s, copy);
		ClearStack(s);
		fputc('\n', fp);
		if (ch != EOF) {
			ch = getchar();
		}
	}
	DestoryStack(s);
}

int main(int argc, const char *argv[])
{
	fp = fopen("com.txt", "w");
	if (fp) {
		LineEdit();
		close(fp);
	}
	printf("file open error\n");
	return 0;
}
