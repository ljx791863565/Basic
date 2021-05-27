#include <iostream>
#include <string>
#include <vector>
#include <string.h>


void split(std::vector<std::string> &dst_strs, const std::string& src_str, const std::string& delimiter)
{
	if (src_str.size()==0){
		return;
	}
	char* token = strtok(const_cast<char*>(src_str.c_str()), delimiter.c_str());
	while (token != nullptr){
		dst_strs.emplace_back(token);
		token = strtok(nullptr, delimiter.c_str());
	}
}

//利用string函数实现
std::vector<std::string> split(const std::string& src_str, const std::string& demil)
{
	std::vector<std::string> result;
	if(src_str.empty()){
		return std::move(result);
	}
	std::size_t size = src_str.size();
	size_t pos = 0;
	size_t start = 0;
	while (pos < size){
		pos = src_str.find(demil, start);
		if (pos != std::string::npos){
			result.emplace_back(src_str.substr(start, pos - start));
		}else {
			if (start <size){
				result.emplace_back(src_str.substr(start, size - start));
			}
			break;
		}
		++pos;
		start = pos;
	}
	return std::move(result);
}

inline TEST

int main(int argc, const char *argv[])
{
	std::vector<std::string> dst_str;

	std::string s {"abdshjf&&i&&djnekjf&&hfhh"};
	std::string s1 {"112,32, 332, , 343"};
	std::string d {" "};

//	split(dst_str, s, d);
	dst_str = split(s1, d);
	for (auto sd:dst_str)
		std::cout << "[" << sd << "]" << ",";
	std::cout << std::endl;
	return 0;
}
