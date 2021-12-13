#include <iostream>
#include <functional>

void output(int x, int y)
{
	std::cout << x << " " <<  y << std::endl;
}

int main(int argc, const char *argv[])
{
	// 本质上 bind传入一个可调用对象及该对象所有参数 返回一个可调用对象 这样的好处是可以比如可调用对象需要两个参数，但是bind之后可以变成
	// 只需要一个或者不需要参数的可调用对象 用于适配不同的需求 同时占位符可以替代参数或者改变传入参数顺序 
	// std::function<void(int, int)> fr = bind(output, 1, 1);
	// fr();
	//
	// 占位符std::placeholders::_n可以替代要传入的参数传给这个要bind的可调用对象 这样该可调用对象在调用时就按_n的顺序来获取参数

	// 没有占位符std::placeholders::_n 此时output函数参数将是固定的两个参数
	// 输出1 2
	std::bind(output, 1, 2)();

	// _1占位符在bind定义的第一个参数，指示被绑定函数(即output)的第一个参数是bind传入的第一个参数4  第二个参数为固定参数2
	// 输出4 2
	std::bind(output, std::placeholders::_1, 2)(4);
	
	// _1占位符在bind定义的第二个参数，指示被绑定函数的第二个参数是bind传入的第一个参数3
	// 输出2 3
	std::bind(output, 2, std::placeholders::_1)(3);

	// 两个占位符分别占位了output函数的第一个和第二个参数 其中第一个参数是bind传入的第二个参数3 第二个参数是bind传入的第一个参数 2
	// 输出3 2
	std::bind(output, std::placeholders::_2, std::placeholders::_1)(2, 3);

	return 0;
}
