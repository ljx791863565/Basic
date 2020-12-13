#include <iostream>

class A
{
private:
	int a;
	double b;
	std::string c;
public:
	A()
	{
		std::cout << "this is class A " << std::endl;
	}
	A(int i)
		:a(i)
	{
		std::cout << "a = " << a << std::endl;
	}

	A(int i, double j)
		:a(i), b(j)
	{
		std::cout << "a = " << a << " b = " << b << std::endl;
	}

	A(int i, double j, std::string s)
		:a(i), b(j), c(s)
	{
		std::cout << "a = " << a << " b = " << b << " c = " << c << std::endl;
	}

//	virtual void fun()
	void fun()
	{
		std::cout << "function fun in class A" << std::endl;
	}
};

class B :public A
{
public:
	using A::A;
//	void fun()
//	{
//		std::cout << "function fun in class B" << std::endl;
//	}
};

int main(int argc, const char *argv[])
{
	B b{1, 2.3, "hello"};	
	b.A::fun();
//	A *a = new A;
//	a->fun();
//	a = &b;
//	a->fun();
	return 0;
}
