#include <iostream>
#include <stdio.h>
#include <stdlib.h>

/*
 * 未初始化的全局变量和静态变量存放在BBS段(bss segment)，程序将在main函数运行之前全部初始化为0， 所有的初始化为0的全局变量和静态变量也存放在BBS段
 * 已经初始化的全局和静态变量存放在数据段(data segment)
 * 在以前的 C 语言中，全局变量和静态变量又分为
 * 　　　　全局初始化区(DATA段) ：存储程序中已初始化的全局变量和静态变量
 * 　　　　未初始化段(BSS段)：存储未初始化的全局变量和静态变量（局部+全局）。BSS段在DATA段的相邻的另一块区域。
 * 　　　　　　　　　　　　　　BBS段特点：在程序执行前BBS段自动清零，所以未初始化的全局变量和静态变量在程序执行前已经成为
 * 在 C++ 里面没有这个区分了，他们共同占用同一块内存区
 *
 * 代码段(text segment) 在最底部，包括只读储存区和文本区，只读储存区存放字符串常量，文本区存放代码和机器码
 *
 * 栈区(Stack)使用栈空间存储函数的返回地址、参数、局部变量、返回值，从高地址向低地址增长。
 * 在一个进程中，位于用户虚拟地址空间顶部的是用户栈，编译器用它来实现函数的调用。其操作方式类似于数据结构中的栈
 *
 * 堆区(Heap)存放由malloc或者new申请的内存空间，由程序员自己释放，若程序员不释放，程序结束时可能由OS回收。
 * 从低地址向高地址增长。分配小内存时使用该区域。  堆的起始地址由mm_struct 结构体中的start_brk标识，结束地址由brk标识
 *
 * memory mapping segment(映射区)存储动态链接库等文件映射、申请大内存（malloc时调用mmap函数）
 * 
 */
int nGlobal = 100;
int nGlobal2;
static int nGlocalStatic = 100;
static int nGlocalStatci2;
int main(int argc, const char *argv[])
{
	char *pLocalString1 = "LocalString1";
	const  char *pLocalString2 = "LocalString2";

	static int nLocalStatic = 100;
	static int nLocalStatic2;
	int nLocal = 100;
	int nLocal2;
	const int nLocalConst = 100;
	const int nLocalConst2 = 200;

	int *pNew = new int [5];
	char *pMalloc = (char *)malloc(5);
	
	printf("Global variable: %d 0x%x ;%d 0x%x\n",nGlobal, &nGlobal, nGlobal2, &nGlobal2);
	printf("Golbal static variable: %d 0x%x; %d 0x%x\n", nGlocalStatic, &nGlocalStatic, nGlocalStatci2, &nGlocalStatci2);
	
	printf("local expression: 0x%x\n", pLocalString1);
	printf("const local expression: 0x%x\n", pLocalString2);

	printf("local variable: %d 0x%x; %d 0x%x\n", nLocal, &nLocal, nLocal2, &nLocal2);
	printf("local static variable: %d 0x%x; %d 0x%x\n", nLocalStatic, &nLocalStatic, nLocalStatic2, &nLocalStatic2);
	printf("local const variable: %d 0x%x; %d 0x%x\n", nLocalConst, &nLocalConst, nLocalConst2, &nLocalConst2);

	printf("pNew : 0x%x 0x%x\n", pNew, &pNew);
	printf("pMalloc: 0x%x 0x%x\n", pMalloc, &pMalloc);


	return 0;
}
