#ifndef TOKEN_NUMBER_H
#define TOKEN_NUMBER_H
#include "token.h"
namespace calculater {
class TokenNumber: public CToken
{
public:
	explicit TokenNumber(const std::string &s);
	explicit TokenNumber(const double value);
	double getValue() const;
	virtual TokenTpye getTokenType() override final;
	virtual std::string toString() override final;
private:
	double m_value;
	std::string m_orgStr;
};
} /* namespace calculater */
#endif /* end of :TOKEN_NUMBER_H */
