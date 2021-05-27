#include <iostream>

using namespace std;

class Base
{
public:
	Base()
	{
		cout << "this is Base()" << endl;
	}
	virtual ~Base()
	{
		cout << "this is ~Base()" << endl;
	}

	virtual void f(float x) 
	{
		cout << "Base::f(float) " << x << endl;
	}

	void g(float x) 
	{
		cout << "Base::g(float) " << x << endl;
	}

	void h(float x) 
	{
		cout << "Base::g(float) " << x << endl;
	}
};

class Derive : public Base 
{
public:
	Derive()
	{
		cout << "this is Derive()" << endl;
	}
	~Derive()
	{
		cout << "this is ~Derive()" << endl;
	}

	virtual void f(float x) override
	{
		cout << "Derive::f(float) " << x << endl;
	}

	void g(int x)
	{
		cout << "Dervie::g(int) " << x << endl;
	}

	void h(float x)
	{
		cout << "Derive::h(float) " << x << endl;
	}
};

int main(int argc, const char *argv[])
{
	Base *b = new Derive;
	delete b;
	Derive *d = new Derive;
	delete d;

	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	Derive dd;
	Base *pb = &dd;
	Derive *pd = &dd;
	
	//f()函数满足覆盖条件，所以当不同类型的指针指向Derive对象时，都只会调用Derive类的f(float x)函数
	pb->f(3.14f);
	pd->f(3.14f);

	//因为基类中的g(float x)和派生类中的g(int x)满足函数名相同但是参数不同条件，所以无论基类中的g()是否有virtual修饰 
	//都将被派生类中的g(int x)隐藏 
	//隐藏意味着无论基类类型指针和派生类类型指针指向什么对象 都只会调用该类型本身类中的函数g(...)
	pb->g(3.14f);
	pd->g(3);

	//派生类中的h(float x)和基类中的h(float x)满足函数名相同参数也相同条件，但是基类中的h(float x)没有virtual修饰
	//所以基类中的h(float x)也将被派生类中的h(float x)隐藏 
	pb->h(3.14f);
	pd->h(3.14f);

	//隐藏有两个作用 
	//首先，如果基类中的函数被隐藏，且两个类中的同名函数参数不同，那么当想调用派生类中的函数时参数写错了，编译器将会报错，如果没有隐藏机制
	//也没有覆盖掉基类的该函数，那么可能会调用到基类中的匹配类型参数的函数
	//
	//其次，如果一个派生类有多个基类，如果没有隐藏机制，那么在调用一个函数比如h时可能会调用到某个不想调用的基类函数h
	
//	cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
//	Base bb;
//	pb = &bb;
//	pd = &bb;

//	pb->h(3.14f);
//	pd->h(3.14f);
	
	return 0;
}
