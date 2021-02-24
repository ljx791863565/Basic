#include <stdio.h>
#include <string.h>

//i am a student.


void reverseString(char *s, int from, int to)
{
	while (from < to) {
		char temp = s[from];
		s[from++] = s[to];
		s[to--] = temp;
	}
}

void reverseTheWord(char *s)
{
	int n = strlen(s);
	reverseString(s, 0, n-1);

	while (s[0] == ' ') {
		s++;
	}

	char *p = s;
	int i = 0;
	int j = 0;
	int a = 0;
	while (j < n) {
		while (s[j] != ' ' && s[j] != '\0') {
			j++;
		}

		reverseString(s, i, j-1);
		for (int k = 0; k < j; k++) {
			*(p+k) = s[i+k];
		}

		p = p+j -i;
//		printf("%d %d\n", j, i);
		while (s[j] == ' ') {
			j++;
		}
		i = j;
		if (s[j] == '\0')  {
			*p = '\0';
			break;
		}
		*p = ' ';
		p++;
	}
}

int main(int argc, const char *argv[])
{
	char string[20] = "I am a student.";
	printf("%s\n", string);
	reverseTheWord(string);
	printf("%s\n", string);
	return 0;
}

