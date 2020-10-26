#include <iostream>

int main()
{
	int i = 0, &r1 = i;
	double d = 3.14, &r2 = d;

	r2 = 3.1415;
	r2 = r1;
	i = r2;
	r1 = d;
	return 0;
}
