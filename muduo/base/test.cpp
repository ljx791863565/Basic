#include "test.h"
#include <iostream>
using namespace std;



void fun()
{
	cout << "in this sacpe" << endl;
}

int main(int argc, const char *argv[])
{
	ljx::Test t("hello");
	::fun();
	t.fun();
	ljx::fun();
	return 0;
}
