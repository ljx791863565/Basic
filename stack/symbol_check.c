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
			/*
			 * 当遇到左符号 将其压入栈中
			 */
			switch(*p)
			{
				case '(' :
				case '[' :
				case '{' :
				case '<' :
					Push(s, *p++);
					break;
			/*
			 * 当遇到右符号 弹出当前栈顶元素并匹配
			 * 如果不是一对的符号 说明失败
			 * 如果是一对 抵消掉继续下一个 p++ 
			 * 如果到最后发现有一个栈顶元素弹出并匹配不上 说明少了一对符号中的一个
			 */
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

		}
		if (StackEmpty(s)) {
			printf("symbol OK\n");
		}else {
			printf("loss right symbol\n");
		}

	}
}

int main(int argc, const char *argv[])
{
	check();
	return 0;
}
