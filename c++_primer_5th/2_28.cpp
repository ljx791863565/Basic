#include <iostream>

int main()
{
	int i, *const cp;
	int *p1, *const p2;		//错误 常量指针必须初始化  *const类型记为常量指针 
	const int ic, &r = ic;
	const int *const p3;	//错误 常量指针必须初始化
	const int *p;
}
