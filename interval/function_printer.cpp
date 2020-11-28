#include <iostream>
#include <string>
#include <functional>

using namespace std;

typedef int(*pFunc)(int);

void test(pFunc f)
{
	f(1);
}

class Wrapper
{
public:
	static int wrapper_func(int x)
	{
		broker_func(x);
		return 0;
	}
	inline static std::function<int(int)> broker_func;
};

class Target
{
public:
	int target_foo(int x)
	{
		cout << (m * x) << endl;
		return 0;
	}
	void doSomething()
	{
		Wrapper::broker_func = std::bind(&Target::target_foo, this, std::placeholders::_1);
		test(Wrapper::wrapper_func);
	}
	int m = 10;
};

int main(int argc, const char *argv[])
{
	Target t;
	t.doSomething();
	t.m = 100;
	t.doSomething();
	return 0;
}
