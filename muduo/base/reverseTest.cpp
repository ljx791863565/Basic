#include <iostream>
#include <assert.h>
#include <type_traits>
#include <algorithm>
using namespace std;
const char digits[] = "9876543210123456789";
const char *zero = digits + 9;
static_assert(sizeof(digits) == 20, "wrong number of digits");

const char digitsHex[] = "0123456789ABCDEF";
static_assert(sizeof(digitsHex) == 17, "wrong numver of digitsHex");
template <typename T>
size_t convert(char *buf, T value)
{
	T i = value;
	char *p = buf;

	do {
		int lsd = static_cast<int>(i % 10);
		i /= 10;
		//i % 10可能是负数 所以要有一个两边走向的digits数组来确保转换后的*p++是正数
		*p++ = zero[lsd];
	} while (i != 0);
	if (value < 0)  {
		*p++ = '-';
	}
	*p = '\0';
	std::reverse(buf, p);

	return p - buf;
}

size_t convertHex(char *buf, uintptr_t value)
{
	uintptr_t i = value;
	char *p = buf;

	do {
		int lsd = static_cast<int>(i % 10);
		i /= 16;
		*p++ = digitsHex[lsd];
	} while (i != 0);
	*p = '\0';
	std::reverse(buf, p);

	return p - buf;
}

int main(int argc, const char *argv[])
{
	char str[100] = {0};
	convert(str, -1100);
	std::cout <<str << std::endl;
	return 0;
}
