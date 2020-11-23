#include <iostream>

int main(int argc, const char *argv[])
{
	//数组定义
	//查看定义类型一般由右向左推导
	int a[10];		//定义了一个一维整型数组 数组大小为10 元素类型为int
	std::cout << "&a =" << &a << " " << "&a[0] =" << &a[0] << " " << "sizeof(a) = " << sizeof(a) << " " << "&a[9] = " << &a[9] << std::endl; 
	int a2[10][10];	//定义了一个二维整型数组 数组大小为10 元素为一维整型数组 其大小为10 其元素为int
	std::cout << "&a2 = " << &a2 << " " << "&a2[0][0] = " << &a2[0][0] << " " << "sizeof(a2) =" << sizeof(a2) << std::endl;
	int (*pstr)[10] = a2;		//定义了一个数组指针 指向一个大小为10元素类型为int的数组
	std::cout << &pstr << std::endl;
	return 0;
}
