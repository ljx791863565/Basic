#ifndef BRACKETS_OPERATOR_H
#define BRACKETS_OPERATOR_H
#include "token_operator.h"
namespace calculater {
#define UNUSED_WARN(x) (x.getValue())

class LeftBrackets : public TokenOperator
{
public:
	explicit LeftBrackets()
	{}
	virtual ~LeftBrackets()
	{}
	virtual OperatorType getOperatorType() override final 
	{
		return OperatorType::LEFT_BRACKETS;
	}

	virtual OperatorPriority getOperatorPriority() override final
	{
		return OperatorPriority::LEFT_BRACKERS_LEVEL;
	}
	virtual std::string toString() override final
	{
		return "(";
	}
	virtual TokenNumber compute(const TokenNumber &lhs, const TokenNumber &rhs) override final 
	{
		UNUSED_WARN(rhs);
		return lhs;
	}
};
class RightBrackets : public TokenOperator
{
public:
	explicit RightBrackets()
	{}
	virtual ~RightBrackets()
	{}
	virtual OperatorType getOperatorType() override final 
	{
		return OperatorType::RIGHT_BRACKETS;
	}

	virtual OperatorPriority getOperatorPriority() override final
	{
		return OperatorPriority::RIGHT_BRACKERS_LEVEL;
	}
	virtual std::string toString() override final
	{
		return ")";
	}
	virtual TokenNumber compute(const TokenNumber &lhs, const TokenNumber &rhs) override final 
	{
		UNUSED_WARN(rhs);
		return lhs;
	}
};
} /* namespace calculater */
#endif /* end of :BRACKETS_OPERATOR_H */
