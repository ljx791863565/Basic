#include <iostream>

void PrintT(int &t)
{
	std::cout << "lvaue" << std::endl;
}

template <typename T>
void PrintT(T && t)
{
	std::cout << "rvalue" << std::endl;
}

template <typename T>
void TestForward(T && v)
{
	PrintT(v);
	PrintT(std::forward<T>(v));
	PrintT(std::move(v));
}

int main(int argc, const char *argv[])
{
	/*
	 * 1是右值，所以未引用类型T && v被初始化为右值引用，但在TestForward内部v变成了具名变量,是左值引用，调用PrintT(int &t)
	 * forward转发的v将被按照原参数类型转发 是右值引用 调用PrintT(T &&t)
	 * move()语义将参数转化为一个右值 调用printT(T &&t)
	 */ 
	TestForward(1);
	int x = 1;
	/*
	 * x是左值，作为T && v参数时转化为左值引用 在TestForward内部也是左值，调用PrintT(int &t)
	 * 通过forward完美转发后依旧是左值引用，调用printT(int &t)
	 * 通过move()语义将会变成右值引用 调用printT(T && t)
	 */ 
	TestForward(x);
	/*
	 * TestForward(T && v)类型是为定义的引用，v是一个左值
	 * forward转发x是左值，被一个左值x初始化为左值引用 调用printT(T && x)
	 * 
	 */ 
	TestForward(std::forward<int>(x));
	return 0;
}
