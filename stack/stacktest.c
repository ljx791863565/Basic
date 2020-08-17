#include "../basic.h"
#include "stack.h"
Status visit(Elemtype e)
{
	printf("%d ", e);
	return OK;
}

int main(int argc, const char *argv[])
{
	Stack *s = (Stack *)malloc(sizeof(Stack));
	Elemtype e;
	int i;
	if (InitStack(s) == OK) {
		for (i = 0; i < 12; i++) {
			Push(s, i);
		}
	}

	int ret = StackEmpty(s);
	if (ret) {
		printf("栈为空\n");
	}else {
		printf("栈不为空\n");
	}

	printf("栈中的元素为：");
//	StackTraverse(s, visit);
	
	GetTop(s, &e);
	printf("栈顶元素为 e=%d\n", e);

	Pop(s, &e);
	printf("弹出栈顶元素 e= %d\n", e);

	GetTop(s, &e);
	printf("栈顶元素为 e=%d\n", e);

	//遍历函数会让base指针从栈低升到栈顶 等于top指针 相当于栈此时为空
	//所以在调用遍历函数后不能再对栈有任何操作
	StackTraverse(s, visit);
//	ClearStack(s);
	ret = StackEmpty(s);
	if (ret) {
		printf("清空栈后 栈为空\n");
	}else {
		printf("栈清空失败\n");
	}
/*
 * 调用销毁栈后会报错段错误 现在不知道问题在哪
	ret = DestoryStack(s);
	if (ret == OK) {
		printf("栈销毁成功\n");
	}else {
		printf("栈销毁失败\n");
	}
*/
	return 0;
}
