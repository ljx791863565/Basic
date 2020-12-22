#include "StringPiece.h"
#include <iostream>


using namespace muduo;
int main(int argc, const char *argv[])
{
	StringPiece sp1;
	StringPiece sp2("hello");
	char buf[100] {"c++ java php"};
	StringPiece sp3(buf);

	cout << sp1 << endl;
	cout << sp2 << endl;
	cout << sp3 << endl;
	return 0;
}
