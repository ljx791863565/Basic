#include <iostream>
#include <string>
#include <vector>
#include <cctype>
void Up(std::string &str)
{
	for (auto &s : str) {
		s = toupper(s);
	}
}

int main(int argc, const char *argv[])
{
	std::vector<std::string> v;
	std::string str {0};
	while (std::cin >> str) {
		v.push_back(str);
		std::cout << "size = " << v.size() << std::endl;
		for (auto &item : v) {
			std::cout << item << " ";
			Up(item);
			std::cout << "To Upper: " << std::endl;
			std::cout << item << " ";
		}
		std::cout << std::endl;
	}
	return 0;
}
