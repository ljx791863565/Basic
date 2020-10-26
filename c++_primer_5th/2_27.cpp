#include <iostream>

int main()
{
	int i = -1, &r = 0;
//	const int i = -1, &r = 0;
	const int i2 = i, &r = i;
	const int *p1 = &i2;
	int *const p2 = &i2;
	const int *const p3 = &i2;
	const int &const r2;
}
