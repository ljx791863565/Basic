#include "mul_operator.h"
namespace calculater {
TokenNumber MulOperator::compute(const TokenNumber &lhs, const TokenNumber &rhs)
{
	return TokenNumber(lhs.getValue() * rhs.getValue());
}

std::string MulOperator::toString()
{
	return "*";
}
} /* namespace calculater */
