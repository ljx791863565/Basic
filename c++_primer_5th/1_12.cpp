#include <iostream>

int main()
{
	int val;
	int sum = 0;
	for (val = -100; val <= 100; val++) {
		sum += val;
	}
	std::cout << "sum = " << sum << std::endl;
	return 0;
}
