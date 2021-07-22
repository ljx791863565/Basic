#include <iostream> 

/*
 * 能被当作函数调用的不一定是函数，也可以是
 * 1）存放函数入口地址的函数指针
 * 2）实现了operator()的类对象。也成为仿函数 
 * 3）可以被转换成函数指针的类对象
 *
 * 以上三类被称为可调用类型 
 * 函数对象实际上是一个function类模版的实例化对象 封装了以上三种可调用对象的任意一种
 */ 

using namespace std;

void fun(void)
{
	cout << __FUNCTION__ << endl;
}

class Foo {
public:
	void operator()(void)
	{
		cout << __FUNCTION__ << endl;
	}

};

class Bar {
public: 
	using fr_t = void (*)(void);

	// operator 隐式转换函数指针类型 返回的函数需要是static
	operator fr_t(void) const 
	{
		return func;
	}
private:
	static void func(void)
	{
		std::cout << __FUNCTION__ << "this is the func" << std::endl;
	}
};

int main()
{
	// 函数不是可调用的类型
	fun();

	// 函数指针是可调用的类型
	void (*pfun)(void) = fun;
	pfun();

	// 仿函数形式是可调用类型
	Foo foo;
	foo();

	// 可以被转换成函数指针的类对象是可调用类型
	Bar bar;
	bar();


	// 使用std::functioon
	function<void(void)> f1 = fun;
	f1();

	function<void(void)> f2 = pfun;
	f2();

	function<void(void)> f3 = foo;
	f3();

	function<void(void)> f4 = bar;
	f4();


	return 0;
}
