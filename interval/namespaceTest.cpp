#include <iostream>

namespace ljx
{
	int s = 100;
};

int main(int argc, const char *argv[])
{
	int s = 200;
	std::cout << s << std::endl;
	std::cout << ljx::s  << std::endl;
	return 0;
}
