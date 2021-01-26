#include <iostream>
#include <stdlib.h>
class DivTest
{
public:
	void div(int *array, int size)
	{
		for (int i = size-1; i >=0 ; i--) {
			if (array[0] == 0)  {
				std::cout << "div is not 0" << std::endl;
				exit(1);
			}
			array[i] /= array[0];
		}
	}
};

int main(int argc, const char *argv[])
{
	int array[10] = {10, 100, 200, 300, 400, 500, 600, 700, 800, 900};

	DivTest dt;
	dt.div(array, 10);

	for (int i = 0; i < 10; i++) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
	return 0;
}
