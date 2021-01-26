#include "token_number.h"
#include <stdlib.h>

namespace calculater {
TokenNumber::TokenNumber(const std::string &s)
{
	m_orgStr = str;
	m_value = atof(str.c_str());
}

TokenNumber::TokenNumber(const double value)
{
	m_value = value;
}

double TokenNumber::getValue() const
{
	return m_value;
}

TokenType TokenNumber::getTokenType()
{
	return TokenType::NUMBER;
}

std::string TokenNumber::toString()
{
	if (m_orgStr.length() > 0)  {
		return m_orgStr;
	} else {
		char buf[128] = {0};
		sprintf(buf, "%f", m_value);
		return std::string(buf);
	}
}
} /* namespace calculater */
