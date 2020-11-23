#ifndef __BIG_NUMBER_H__
#define __BIG_NUMBER_H__

#include <string>
#include <cstdlib>
#include <climits>

typedef long long INT_64;
class BigNumber
{
public:
	BigNumber()
	{
		m_data = 0;
		m_str = "\0";
	}

	BigNumber(INT_64 value);
	BigNumber(std::string &s);
	BigNumber(int n, char c);
	BigNumber(const BigNumber &bn);
	BigNumber& operator=(const BigNumber &bn);

private:
	INT_64 m_data;
	std::string str_data;
};
#endif
