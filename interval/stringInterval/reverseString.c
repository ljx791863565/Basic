#include <stdio.h>
#include <string.h>

void ReverseString(char *s, int from, int to)
{
	while (from < to) {
		char temp = s[from];
		s[from++] = s[to];
		s[to--] = temp;
	}
}

void leftRotateString(char *s, int n, int m)
{
	//n为字串s的长度
	//m为第一部分子串长度
	//假设 s="abcdefghi"
	//n=9
	//m=7
	//结果为
	//	第一步 "gfedcbahi"
	//	第二步 "gfedcbaih"
	//	第三步 "hiabcdefg"
	m %= n;
	ReverseString(s, 0, m-1);
	ReverseString(s, m, n-1);
	ReverseString(s, 0, n-1);
}

int main(int argc, const char *argv[])
{
	char string[20] = "abcdefghi";

	printf("%s\n", string);
	leftRotateString(string, strlen(string), strlen(string)-2);
	printf("%s\n", string);
	return 0;
}
