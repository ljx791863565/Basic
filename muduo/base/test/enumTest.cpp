#include <iostream>

class A
{
	enum color
	{
		BLUE,
		RED,
		YELLOW
	};
	static color color();
};

extern A::color g_clolr;
inline A::clolr A::clolr()
{
	return g_color;
}

int main(int argc, const char *argv[])
{
	if (A::color() < A::RED)  {
	
	}
	return 0;
}
