#include <iostream>
#include <string.h>
#include <stdio.h>
class CString{
public:
	CString(char *p_data = nullptr)
	{
		if (p_data == nullptr)  {
			m_data = new char[1];
			m_data[0] = '\0';
		}else {
			m_data = new char[strlen(p_data) +1];
			strcpy(m_data, p_data);
		}
	}

	CString(const CString &str)
	{
		m_data = new char[strlen(str.m_data)+1];
		strcpy(m_data, str.m_data);
	}

	CString & operator=(const CString &str)
	{
		if (this == &str)  {
			return *this;
		}
		delete [] m_data;
		m_data = nullptr;
		m_data = new char[strlen(str.m_data) +1];
		strcpy(m_data, str.m_data);
		return *this;
	}

	~CString()
	{
		delete [] m_data;
	}

	void print()
	{
		printf("%s", m_data);
	}
private:
	char *m_data;
};

//=========================测试代码=========================
void Test1()
{
	printf("test1 begins:\n");
	char *text = "Hello world";

	CString str1(text);
	CString str2;
	str2 = str1;
	printf("the expected result is :%s.\n", text);
	printf("the actual result is: ");
	str2.print();
	printf(".\n");
}

void Test2()
{
	printf("Test2 begins:\n");
	char *text = "Hello world";
	CString str1(text);
	str1 = str1;
	printf("the expected result is :%s.\n", text);
	printf("the actual result is: ");
	str1.print();
	printf(".\n");
	
}

void Test3()
{
	printf("Test3 begins:\n");
	char *text = "Hello world";
	CString str1(text);
	CString str2, str3;
	str3 = str2 = str1;
	printf("the expected result is :%s.\n", text);
	printf("the actual result is: ");
	str2.print();
	printf(".\n");

	printf("the expected result is :%s.\n", text);
	printf("the actual result is: ");
	str3.print();
	printf(".\n");

}

int main(int argc, const char *argv[])
{
	Test1();
	Test2();
	Test3();
	return 0;
}



