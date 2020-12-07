#include <iostream>

int main()
{
	int i;					//未初始化变量 其值未知
	int i2 = 0;				//初始化变量 
	const int i3 = 0;		//常量
	
	int *p = &i;			//指向类型变量的指针 其值为变量地址  通过*p解引用改变i值
	const int *p1 = &i3;	//指向常量的指针 想要存放常量对象的地址只能通过指向常量的指针 不能用于改变其所指对象的值 
	p1 = &i2;				//但是指向常量的指针也可以指向非常量对象
	int *const p2 = &i;		//常量指针 必须初始化 一但初始化后其值(即保存的那个地址)就不可改变 p2 = p是错误的 但是其指向的对象值可以改变 *p2 = 10是正常的
	const int *const p3 = &i;	//这样是一个指向常量对象的常量指针 那么其值不可改变 也不可以通过这个指针改变它指向对象的值 

	int &r = i;				//指向int类型变量i的引用 必须定义时初始化 改变r的值就是改变i的值 r只是i的别名 
	const int &r2 = i3;		//对常量的引用 绑定在const对象上的引用 不可以修改它引用的对象 因为对象是const的
	const int &r3 = i2;		//同样的 常量引用可以指向非常量对象 字面值 甚至表达式 const int &r4 = 42; const int &r5 = r4*2;

}