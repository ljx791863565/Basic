#ifndef CALC_TYPE_DEFINE_H
#define CALC_TYPE_DEFINE_H

namespace calculater {
enum class TokenType
{
	OPERATOR,
	NUMBER,
	UNKNOWN,
};

enum class OperatorType
{
	UNKNOWN_OPERATOR = 0,
	ADD_OPERATOR,
	SUB_OPERATOR,
	MUL_OPERATOR,
	DIV_OPERATOR,
	LEFT_BRACKETS,
	RIGHT_BRACKETS,
	OTHER_OPERATOR,
};

enum class OperatorPriority
{
	UNKNOWN_LEVEL=0,
	ADD_LEVEL,
	NUL_LEVEL,
	LEFT_BRACKETS_LEVEL,
	RIGHT_BRACKETS_LEVEL,
};
} /* namespace calculater */
#endif /* end of :CALC_TYPE_DEFINE_H */
