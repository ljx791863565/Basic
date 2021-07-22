#include <iostream>

using namespace std;

int g_constructCount = 0;
int g_copyConstructCount = 0;
int g_destructCount = 0;

class A{
public:
	A() 
	{
		cout << "construct " << ++ g_constructCount << endl;
	}
	A(const A& a)
	{
		cout << "copyConstruct " << ++g_copyConstructCount << endl;
	}
	~A()
	{
		cout << "destruct " << ++g_destructCount << endl;
	}
};

A GetA()
{
	return A();
}

int main(int argc, const char *argv[])
{
	A a = GetA();
	return 0;
}

// 编译时禁止编译器优化构造函数  -fno-elide-constructors
// construct 1						GetA()使用构造函数构造了一个对象aa
// copyConstruct 1					GetA()中的对象aa返回时使用拷贝构造了宇哥temp对象
// destruct 1						GetA()返回后aa对象被析构
// copyConstruct 2					main()中的temp临时对象拷贝构造了对象a
// destruct 2						析构temp临时对象
// destruct 3						析构a对象
