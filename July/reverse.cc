/*
 * 字符串翻转 
 * 给定一个长度n字符串，要求将前m (m <= n) 个字符移动到字符串尾部，要求空间复杂度1
 * 例如 "abcdef" ,将前3个字符翻转后，得到 "defabc"
 */ 

#include <stdio.h>
#include <string.h>

#ifndef NO_DEBUG
#include <assert.h>
#endif

// 第一种暴力解法 每次移动一个字符到字符串末尾 依次移动m次
// 时间复杂度 O(m*n) 
// 空间复杂度 1
static void LeftShiftOne(char *str, int n)
{
	char ch = str[0];
	for (int i = 1; i < n; i++) {
		str[i-1] = str[i];
	}
	str[n-1] = ch;
}

static void reverse(char *str, int n, int m)
{
	while (m--) {
		LeftShiftOne(str, n);
	}
}


// 第二种解法 把一个字符串分成需要移动的和不需要移动的两段 分别将其逆转 最后整个字符串逆转即可
// 例如 "abcdef" 将其分为 "abc" "def" 分别逆转 得到 "cba" "fed" 再次全字符串逆转 "defabc" 
// 时间复杂度为 O(n1) + O(n2) + O(n) n = n1+n2  可得复杂度为O(n)
// 空间复杂度 1

// 翻转某个子串
static void reverseString(char *str, int begin, int end)
{
	assert(begin <= end);
	
	while (begin < end) {
		char ch = str[begin];
		str[begin++] = str[end];
		str[end--] = ch;
	}
}

static void reverse2(char *str, int n, int m)
{
	// 三步法 翻转第一个串 翻转剩余串 翻转整个串
	m %= n;
	reverseString(str, 0, m-1);
	reverseString(str, m, n-1);
	reverseString(str, 0, n-1);
}

int main()
{
	char str[] = "abcdef";

	printf("str = %s\n", str);

	// reverse(str, strlen(str), 3);
	reverse2(str, strlen(str), 3);

	printf("-----------------reverse:-------------------\n");

	printf("str = %s\n", str);

	return 0;
}
