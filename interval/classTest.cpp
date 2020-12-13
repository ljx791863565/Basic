#include <iostream>

using namespace std;

/*
 * 当类中没有定义任何构造函数时，编译器会自动分配默认无参构造函数
 * 当定义了自己的构造函数时，编译器将不会分配任何构造函数
 * 所以如果没有自定义无参构造函数时，使用无参数深明定义类将会报错没有合适的构造函数
 */ 

int cc = 20;
class A
{
public:
	A() = default;
	A(int num, const int numb = 10)
		:a(num), b(numb), c(a)
	{}
private:
	int a;
	const int b = 20;
	int &c = a;
};

int main(int argc, const char *argv[])
{
	A *a = new A;
	A aa;
	A ab(aa);
	return 0;
}
