#ifndef MUL_OPERATOR_H
#define MUL_OPERATOR_H

#include "token_operator.h"

namespace calculater {
class MulOperator: public tokenOperator
{
public:
	explicit MulOperator()
	{}
	virtual ~MulOperator()
	{}
	virtual OperatorType getOperatorType() override final
	{
		return OperatorType::MUL_OPERATOR;
	}
	virtual OperatorPriority() override final
	{
		return OperatorPriority::MUL_LEVEL;
	}
	TokenNumber compute(const TokenNumber &lhs, const TokenNumber &lhs) override final;
	virtual std::string toString() override final;
};
} /* namespace calculater */
#endif /* end of :MUL_OPERATOR_H */
