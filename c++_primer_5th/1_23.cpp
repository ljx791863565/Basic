#include <iostream>
#include "Sales_item.h"

int main()
{
	Sales_item book;
	if (std::cin>> book) {
		Sales_item trans;
		while (std::cin >> trans) {
			if (trans.isbn() == book.isbn()) {
				book += trans;
			}else {
				std::cout << book << std::endl;
				book = trans;
			}
		}
		std::cout << book << std::endl;
	}else {
		std::cerr << "No data!" << std::endl;
		return -1;
	}
	return 0;
}
