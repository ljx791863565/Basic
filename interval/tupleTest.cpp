#include <iostream>
#include <tuple>
#include <string>

#include "printtuple.h"

int main(int argc, const char *argv[])
{
	std::tuple<int, float, std::string> t(10, 1.0, "s");
	std::cout << std::tuple_size<decltype(t)>::value << std::endl;
	std::tuple_element<0,decltype(t)>::type cnt1 = std::get<0>(t); 
	std::tuple_element<1,decltype(t)>::type cnt2 = std::get<1>(t); 
	std::tuple_element<2,decltype(t)>::type cnt3 = std::get<2>(t); 
	std::cout << cnt1 << std::endl;
	std::cout << cnt2 << std::endl;
	std::cout << cnt3 << std::endl;

	std::cout << t << std::endl;
	return 0;
}
