#include <iostream>
#include "Range.h"
using namespace range;
using namespace std;
void test_range(void)
{
	cout << "Range(15):";
	for (auto i : Range(15)) {
		cout << " " << i;
	}
	cout << endl;
	
	cout << "Range(2, 6):";
	for (auto i : Range(2, 6)) {
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(2, 6, 3):";
	for (auto i : Range(2, 6, 3)) {
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(-2, -6, -3):";
	for (auto i : Range(-2, -6, -3)) {
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(10.5, 15.5):";
	for (auto i : Range(10.5, 15.5)) {
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(35, 27, -1):";
	for (auto i : Range(35, 27, -1)) {
		cout << " " << i;
	}
	cout << endl;

	cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z')) {
		cout << " " << i;
	}
	cout << endl;
/*
	cout << "Range(2, 8, 0.5):";
	for (auto i : Range(2, 8, 0.5)) {
		cout << " " << i;
	}
	cout << endl;

	cout << "Range(8, 7, -0.1):";
	for (auto i : Range(8, 7, -0.1)) {
		cout << " " << i;
	}
	cout << endl;
*/
}

int main(int argc, const char *argv[])
{
	test_range();
	return 0;
}
