#include <iostream>
#include <cstdlib>
#include <string>
int main(int argc, const char *argv[])
{
	std::string s1{"10"};
	std::string s2{"3.1415"};
	std::string s3{"-4.3"};
	std::string s4{"this is not number"};

	std::cout << std::atoi(s1.c_str()) << std::endl;
	std::cout << std::atoi(s2.c_str()) << std::endl;
	std::cout << std::atoi(s3.c_str()) << std::endl;
	std::cout << std::atoi(s4.c_str()) << std::endl;
	return 0;
}
