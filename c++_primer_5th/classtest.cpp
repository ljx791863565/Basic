#include <iostream>

class B;
class A
{
public:
	B *b;
};

class B
{
public:
	A a;
};

int main(int argc, const char *argv[])
{
	
	return 0;
}
