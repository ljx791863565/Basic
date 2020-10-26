#ifndef __STRING_H__
#define __STRING_H__
#include <iostream>
#include <string.h>

class String
{
public:
	String()
	{
		m_data = new char[1];
		*m_data = '\0';
		m_len = 0;
	}

	String(const char *str)
	{
		m_len = strlen(str);
		m_data = new char[m_len+1];
		strcpy(m_data, str);
	}

	String(const String &s)
	{
		m_len = s.m_len;
		m_data = new char[m_len + 1];
		strcpy(m_data, s.m_data);
	}


private:
	char *m_data;
	int m_len;
};
#endif //__STRING_H__
