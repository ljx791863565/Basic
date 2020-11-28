#ifndef __STACK_H__
#define __STACK_H__
#include "../basic.h"

#define STACK_INIT_SIZE 100		//栈的储存初始化分配空间
#define STACK_INCREMENT 10		//栈的储存分配空间增量
typedef struct {
	Elemtype *base;
	Elemtype *top;
	int stacksize;
} Stack;
#endif //__STACK_H__
