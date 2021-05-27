#include <iostream>
#include <string>
#include <vector>


void show(vector<T> &v)
{
	std::cout << "vector size is: " << v.size() << std::endl;
	for (auto &e : v)
		std::cout << e << " ";
	std::cout<<std::endl;
}

int main(int argc, const char *argv[])
{

	vector<int> v1;
	vector<int> v2(10);
	vector<int> v3(10, 42);
	vector<int> v4 {10};
	vector<int> v5 {10, 42};
	vector<std::string> v6 {10};
	vector<std::string> v7{10, "hi"};

	show(v1);
	show(v2);
	show(v3);
	show(v4);
	show(v5);
	show(v6);
	show(v7);
	return 0;
}
