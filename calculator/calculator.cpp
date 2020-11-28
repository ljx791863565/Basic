#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "stack.c"
#include <ctype.h>

#define MAXSIZE 128
using namespace std;

void delSpace(const char *str, char *RPstr)
{
	if (str == NULL) {
		return;
	}
	int j = 0;
	while (*str != '\0') {
		if (isdigit(*str) || *str == '(' || *str == ')' || *str == '+' || *str == '-' || *str == '*' || *str == '/') {
			RPstr[j] = *str;
			j++;
		}
		str++;
	}
}

Elemtype Top(Stack *s)
{
	if (s->top == s->base) {
		exit(0);
	}
	return *(s->top-1);
}

void Reverse_polish(char *RPstr, char *temp)
{
	if (RPstr == NULL) {
		return; 
	}
	Stack s1;
	Stack s2;

	InitStack(&s1);
	InitStack(&s2);
	Push(&s1, '#');
	int length = 0;
	char *p = RPstr;
	char ch = '0';
	for (; *p != '\0'; p++) {
		switch (*p)
		{
			case '(':
				Push(&s1, *p);
				break;
			case ')':
				while (Top(&s1) != '(') {
					Pop(&s1, &ch);
					Push(&s2, ch);
				}
				Pop(&s1, &ch);
				break;
			case '+':
			case '-':
				for (ch = Top(&s1); ch != '#'; ch = Top(&s1)) {
					if (ch == '(') {
						break;
					}else {
						Pop(&s1, &ch);
						Push(&s2, ch);
					}
				}
				Push(&s1, *p);
				length++;
				break;
			case '*':
			case '/':
				for (ch = Top(&s1); ch != '#' && ch != '+' && ch != '-'; ch = Top(&s1)){
					if (ch == '(') {
						break;
					}else {
						Pop(&s1, &ch);
						Push(&s2, ch);
					}
				}
				Push(&s1, *p);
				length++;
				break;
			default:
				Push(&s2, *p);
				length++;
		}
	}
	while (!StackEmpty(&s1) && Top(&s1) != '#') {
		Pop(&s1, &ch);
		Push(&s2, ch);
	}
	
	temp+=length;
	*temp = '\0';
	temp--;
	for(; !StackEmpty(&s2); temp--){
		Pop(&s2, &ch);
		*temp = ch;
	}
	++temp;
}

int calculator(char *str)
{
	if (str == NULL) {
		exit(0);
	}
	Stack s;
	InitStack(&s);
	char *p = str;
	char ch1, ch2, ch;
	int sum = 0;
	while (*p != '\0') {
		switch(*p) 
		{
			case '+':
				Pop(&s, &ch1);
				Pop(&s, &ch2);
				ch = ch1 + ch2;
				Push(&s, ch);
				p++;
				break;
			case '*':
				Pop(&s, &ch1);
				Pop(&s, &ch2);
				ch = ch1 * ch2;
				Push(&s, ch);
				p++;
				break;
			case '/':
				Pop(&s, &ch1);
				Pop(&s, &ch2);
				ch = ch1 / ch2;
				Push(&s, ch);
				p++;
				break;
			case '-':
				Pop(&s, &ch1);
				Pop(&s, &ch2);
				ch = ch1 - ch2;
				Push(&s, ch);
				p++;
				break;
			default:
				Push(&s, *p);
				p++;
		}
	}
	sum = Top(&s) - '0';
	return sum;
}

int main(int argc, const char *argv[])
{
	cout << "请输入算式:" << endl;	
	char str[MAXSIZE];
	string s;
	memset(str, 0, sizeof(str));
	cin.getline(str, MAXSIZE, '\n');		
//	printf("%s\n", str);

	char RPstr[MAXSIZE];
	memset(RPstr, 0, sizeof(RPstr));
//	Reverse_polish(str, RPstr);
//	printf("%s\n", RPstr);

	delSpace(str, RPstr);
	char temp[MAXSIZE] = {0};
	Reverse_polish(RPstr, temp);
	printf("%s\n",RPstr);
	printf("%s\n",temp);
	int sum = calculator(temp);
	printf("sum = %d\n", sum);
	return 0;
}
