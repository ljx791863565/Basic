#ifndef DIV_OPERATOR_H
#define DIV_OPERATOR_H

#include "token_operator.h"

namespace calculater {
class DivOperator: public tokenOperator
{
public:
	explicit DivOperator()
	{}
	virtual ~DivOperator()
	{}
	virtual OperatorType getOperatorType() override final
	{
		return OperatorType::DIV_OPERATOR;
	}
	virtual OperatorPriority() override final
	{
		return OperatorPriority::MUL_LEVEL;
	}
	TokenNumber compute(const TokenNumber &lhs, const TokenNumber &lhs) override final;
	virtual std::string toString() override final;
};
} /* namespace calculater */
#endif /* end of :DIV_OPERATOR_H */
