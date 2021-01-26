#ifndef ADD_OPERATOR_H
#define ADD_OPERATOR_H

#include "token_operator.h"

namespace calculater {
class AddOperator: public tokenOperator
{
public:
	explicit AddOperator()
	{}
	virtual ~AddOperator()
	{}
	virtual OperatorType getOperatorType() override final
	{
		return OperatorType::ADD_OPERATOR;
	}
	virtual OperatorPriority() override final
	{
		return OperatorPriority::ADD_LEVEL;
	}
	TokenNumber compute(const TokenNumber &lhs, const TokenNumber &lhs) override final;
	virtual std::string toString() override final;
};
} /* namespace calculater */
#endif /* end of :ADD_OPERATOR_H */
