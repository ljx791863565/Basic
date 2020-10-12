#include <iostream>

int main()
{
	int i;
	int sum = 0;
	for (i = 50; i <= 100; i++) {
		sum += i;
	}
	std::cout << "the 50 to 100 surname is " << sum << std::endl;

	for (i = 10; i >= 0; i--) {
		std::cout << i << std::endl;
	}

	std::cout << "input two numbers :" << std::endl;
	int val1, val2;
	std::cin >> val1 >> val2;
	std::cout << val1 << " to " << val2 << " is: " << std::endl;
	for (i = val1; i <= val2; i++) {
		std::cout << i << std::endl;
	}

	return 0;
}
