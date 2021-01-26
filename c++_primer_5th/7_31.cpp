#include <iostream>

//前向声明 forward declaration
class X;
class Y;

class X
{
public:
	Y *y;
};

class Y
{
public:
	X x;
};


int main(int argc, const char *argv[])
{
	X x;
	Y y;
	return 0;
}
