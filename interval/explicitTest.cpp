#include <iostream>
#include <string>
/*
 * 此处类A的构造函数只有一个string类型参数
 * 如果我使用一个string类型变量传递给一个参数为A类型的函数fun时，这个构造函数会被调用，生成一个A的临时变量传递给函数fun
 * 
 * 这里发生了隐式转换 把string类型转换为了A类型
 *
 * 如果不想发送这样的转换或者不想要生成不必要的A临时变量 可以用explicit修饰A的构造函数
 * 被explicit修饰的构造函数不允许隐式转换 
 * error: could not convert ‘s’ from ‘std::string {aka std::basic_string<char>}’ to ‘A’
 *   fun(s);
 *   函数fun只接受A类型的变量
 *
 * 所有单参数的构造函数必须是显式的
 */

class A
{
public:
	explicit A(std::string s)
	{
		std::cout << "this constructor is celled " << s << std::endl;
	}
	std::string s;
};

void fun(A a)
{
	std::cout << "this func is used class A object " << a.s << std::endl;
}

int main(int argc, const char *argv[])
{
	A a("hello");
	std::string s {"world"};
	/*
	 * this constructor is celled hello
	 * this constructor is celled world
	 * this func is used class A object 
	 *
	 * 可以看到这里调用了A类型的构造函数
	 */
//	fun(s);

	/*
	 * this constructor is celled hello
	 * this func is used class A object 
	 */
	fun(a);
	return 0;
}
