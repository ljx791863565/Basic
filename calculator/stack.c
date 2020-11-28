#include "stack.h"
#include "../basic.h"

//初始化栈
Status InitStack(Stack *s)
{
	s->base = (Elemtype *)malloc(STACK_INIT_SIZE *sizeof(Elemtype));
	if (!s->base)
		exit (OVERFLOW);
	s->top = s->base;
	s->stacksize = STACK_INIT_SIZE;

	return OK;
}

//销毁一个栈 栈不存在base值为NULL
Status DestoryStack(Stack *s)
{
	free(s->base);
	s->base = NULL;
	s->top = NULL;
	s->stacksize = 0;
	return OK;
}

//将栈清空不销毁
Status ClearStack(Stack *s)
{
	s->stacksize = 0;
	s->top = s->base;

	return OK;
}

//判断栈是否为empty 是:true 否:false
Status StackEmpty(Stack *s)
{
	return (s->top == s->base) ? TRUE : FALSE;
}

int StackLength(Stack *s)
{
	return s->stacksize;
}

//获取栈顶元素保存在e地址处 如果空栈 返回ERROR
Status GetTop(Stack *s, Elemtype *e)
{
	//此时栈为空 
	if (s->top == s->base) {
		return ERROR;		
	}
	
	//栈顶元素在top指针下一个
	*e = *(s->top-1);

	return OK;
}

//将元素e压入栈 如果栈满了就先扩容栈
Status Push(Stack *s, Elemtype e)
{
	if (s->top - s->base >= s->stacksize) {
		Elemtype *tmp = (Elemtype *)realloc(s->base, (s->stacksize + STACK_INCREMENT)*sizeof(Elemtype));
		if (!tmp) {
			exit(OVERFLOW);
		}
		s->base = tmp;

		s->top = s->base + s->stacksize;
		s->stacksize += STACK_INCREMENT;
	}
	*(s->top++) = e;

	return OK;
}

//删除栈顶元素 将其值保存在e地址处 如果空栈 返回ERROR
Status Pop(Stack *s, Elemtype *e)
{
	if (s->top == s->base) {
		return ERROR;
	}
	*e = *(s->top-1);
	s->top --;
	return OK;
}

//从栈低依次调用visit遍历到栈顶 如果visit调用失败 即操作失败
Status StackTraverse(Stack *s, Status(*visit)(Elemtype))
{
	while (s->top  > s->base) {
		visit(*s->base++);
	}
	printf("\n");

	return OK;
}
