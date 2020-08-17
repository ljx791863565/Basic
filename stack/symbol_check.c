#include "stack.h"

//任意输入一个字符串 检查其符号是否配对 () []  {} <>
void check()
{
	Elemtype ch[80], *p, e;
	Stack *s = (Stack *)malloc(sizeof(Stack));
	if (InitStack(s)) {
		printf("input string\n");
		fgets(ch, 80, stdin);
		p = ch;
		while (*p) {
			switch(*p)
			{
				case '(' :
				case '[' :
				case '{' :
				case '<' :
					Push(s, *p++);
					break;
				case ')' :
				case ']' :
				case '}' :
				case '>' :
					{
						if (!StackEmpty(s)) {
							Pop(s, &e);
							if ((*p == ')' && e != '(') 
									|| (*p == ']' && e != '[')
									|| (*p == '}' && e != '{')
									|| (*p == '>' && e != '<')) {
								printf("symbol error\n");
								exit(ERROR);
							}else {
								p++;
								break;
							}
						}else {
							printf("loss some symbol\n");
							exit(ERROR);
						}
					}
				default :
					p++;
			}

			if (StackEmpty(s)) {
				printf("symbol OK\n");
			}else {
				printf("loss right symbol\n");
			}
		}

	}
}

int main(int argc, const char *argv[])
{
	check();
	return 0;
}
