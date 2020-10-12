#include <iostream>
#include "Sales_item.h"

int main()
{
	Sales_item book1;
	Sales_item book2;
	std::cin >> book1 >> book2;
	if (book1.isbn() == book2.isbn()) {
		std::cout << book1+book2 << std::endl;
		return 0;
	}else {
		std::cerr << "Data must refer to same ISBN" << std::endl;
		return -1;
	}
	return 0;
}
