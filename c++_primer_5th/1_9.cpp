#include <iostream>

int main()
{
	int val = 50;
	int sum = 0;
	while (val <= 100) {
		sum += val;
		++val;
	}
	std::cout << "the sum of 50 to 100 is " << sum << std::endl;
	return 0;
}
