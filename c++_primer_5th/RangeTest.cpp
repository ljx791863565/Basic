#include "Range.h"

void test_Range(void)
{
	std::cout << "Range(15):";
	for (int i : Range(15))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range(2, 6):";
	for (auto i : Range(2, 6))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	const int x = 2, y = 6, z = 3;
	std::cout << "Range(2, 6, 3):";
	for (auto i : Range(x, y, z))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range(-2, -6, -3):";
	for (auto i : Range(-2, -6, -3))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range(10.5, 15.5):";
	for (auto i : Range(10.5, 15.5))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range(35, 27, -1):";
	for (int i : Range(35, 27, -1))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range(2, 8, 0.5):";
	for (auto i : Range(2, 8, 0.5))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range(8, 7, -0.1):";
	for (auto i : Range(8, 7, -0.1))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
	std::cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z'))
	{
		std::cout << " " << i;
	}
	std::cout << std::endl;
}

int main(int argc, const char *argv[])
{
	test_Range();
	return 0;
}
