#include <stdio.h>
#include <string.h>

// "we are happy."   ==>  "we20%are20%happy."
//

void replaceBlack(char *s, int length)
{
	if (s == NULL && length <= 0)  {
		return;
	}

	int originalLength = 0;
	int blackCount = 0;
	int i = 0;
	while (s[i++] != '\0') {
		++originalLength;
		if (s[i] == ' ')  {
			++blackCount;
		}
	}

	int newLength = originalLength + blackCount*2;
	if (newLength >= length)  {
		return;
	}

	int indexOfOriginal = originalLength;
	int indexOfNew = newLength;
//	s[indexOfNew] = '\0';
	while (indexOfOriginal >= 0 && indexOfNew > indexOfOriginal) {
		if (s[indexOfOriginal] != ' ')  {
			s[indexOfNew--] = s[indexOfOriginal];
		} else {
			s[indexOfNew--] = '0';
			s[indexOfNew--] = '2';
			s[indexOfNew--] = '%';
		}
		--indexOfOriginal;
	}
	
}

int main(int argc, const char *argv[])
{
	char string[20] = "we are happy.";

	replaceBlack(string, sizeof(string));

	printf("%s\n", string);
	return 0;
}
