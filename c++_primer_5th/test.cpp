#include <iostream>

int main()
{
	double d = 3.14, *p = &d;

	void *vp = p;

	int i = 0;

	double *pd = &i;	//此处报错类型不匹配 必须将pd指针用double*类型赋值
	int *pi = i;		//同样报错类型不匹配
	int *pii = &i;

	int null = 0;
	int *np = &null;
}
