#include <stdio.h>


//野指针：指针指向的地址是无效或者不可用的

//产生野指针的情况
//
//1）定义一个指针但是没有初始化，此时该指针指向不明确，使用该指针行为是未定义的
// int *p;
//
// 2) 一个指向堆区的指针被free但未被置为NULL，此时指针还是可以被访问，但其值为非法
// int *p = (int*)malloc(10 *sizeof(int));
// free(p);
// 此时用 if (p != NULL)判断失效
//
// 3）对指针的操作已经超过了指针的作用域
// 比如一个函数返回一个指针变量，但在函数被析构后该变量已经被系统回收了，此时指针为野指针
//
//

#include <stdlib.h>
#include <string.h>

 char * GetMemory(void)
 {
		char str[100] = {0};

		return str;
 }

 int main()
 {
		//此时GetP为野指针
		char *GetP= GetMemory();
		strcpy(GetP, "Hello World");
		printf("%s\n", GetP);
		return 0;
 }
