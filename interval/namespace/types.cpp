#include "types.h"

#include <iostream>
namespace test
{
int test()
{
	string s("hello");
	std::cout << s << std::endl;

	return 0;
}

}

int main(int argc, const char *argv[])
{
	test::test();
	return 0;
}
