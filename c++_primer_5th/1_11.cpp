#include <iostream>

int main()
{
	std::cout << "input two numbers :" << std::endl;
	int val1, val2;
	std::cin >> val1 >> val2;
	std::cout << "the number of " << val1 << " to " << val2 << "is: " << std::endl;
	while (val1 <= val2) {
		std::cout << val1 << std::endl;
		++val1;
	}
	return 0;
}
