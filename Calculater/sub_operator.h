#ifndef SUB_OPERATOR_H
#define SUB_OPERATOR_H

#include "token_operator.h"

namespace calculater {
class SubOperator: public tokenOperator
{
public:
	explicit SubOperator()
	{}
	virtual ~SubOperator()
	{}
	virtual OperatorType getOperatorType() override final
	{
		return OperatorType::SUB_OPERATOR;
	}
	virtual OperatorPriority() override final
	{
		return OperatorPriority::ADD_LEVEL;
	}
	TokenNumber compute(const TokenNumber &lhs, const TokenNumber &lhs) override final;
	virtual std::string toString() override final;
};
} /* namespace calculater */
#endif /* end of :SUB_OPERATOR_H */
