#include <iostream>

int main()
{
	std::cout << "input two numbers :" << std::endl;
	int val1, val2;
	std::cin >> val1 >> val2;
	if (val1 <= val2) {
		std::cout << "the number of " << val1 << " to " << val2 << "is: " << std::endl;
		while (val1 <= val2) {
			std::cout << val1 << std::endl;
			++val1;
		}
	}else {
		std::cout << "the number of " << val2 << " to " << val1 << "is: " << std::endl;
		while (val2 <= val1) {
			std::cout << val2 << std::endl;
			++val2;
		}
	}
	return 0;
}
