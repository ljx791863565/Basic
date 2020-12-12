#ifndef _TEST_H_
#define _TEST_H_

#include <string>
#include <iostream>
namespace ljx
{
class Test
{
public:
	Test(std::string str)
		:s(str)
	{}

	Test(const char *str)
		:s(str)
	{}
	void fun()
	{
		std::cout << "in class Test space " << std::endl;
	}
private:
	std::string s;
};

void fun()
{
	std::cout << "in ljx space " << std::endl;
}
}
#endif /* end of :_TEST_H_ */
