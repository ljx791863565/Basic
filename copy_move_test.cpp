#include <iostream>
#include <vector>
#include <time.h>
#include <array>
int start, stop;

class Myvector
{
	std::vector<int> data;
public:
	Myvector()
	{
		data = std::vector<int>(100, 0);
	}
};

int main(int argc, const char *argv[])
{
	
	std::array<Myvector, 100000> my_vector; 

	start = clock();
	std::array<Myvector, 100000> my_vector1 = my_vector;
	stop = clock();
	std::cout << ((double)stop - start) / CLOCKS_PER_SEC << std::endl;
	
	start = clock();
	std::array<Myvector, 100000> my_vector2 = std::move(my_vector);
	stop = clock();
	std::cout << ((double)stop - start) / CLOCKS_PER_SEC << std::endl;
	return 0;
}
