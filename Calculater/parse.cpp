#include "parse.h"
#include "add_operator.h"
#include "sub_operator.h"
#include "mul_operator.h"
#include "div_operator.h"
#include "barckets_operator.h"
#include "token_number.h"

#include <iostream>
#include <map>
#include <ctype.h>

namespace calculater {

OperatorType StrToOperator(const char ch) noexcept
{
	switch (ch)
	{
		case '+':
			return OperatorType::ADD_OPERATOR;
			break;
		case '-':
			return OperatorType::SUB_OPERATOR;
			break;
		case '*':
			return OperatorType::MUL_OPERATOR;
			break;
		case '/':
			return OperatorType::DIV_OPERATOR;
			break;
		case '(':
			return OperatorType::LEFT_BRACKETS;
			break;
		case ')':
			return OperatorType::RIGHT_BRACKETS;
			break;
		default:
			return OperatorType::UNKNOWN_OPERATOR;
	}
	return OperatorType::UNKNOWN_OPERATOR;
}

std::string OperatorToStr(OperatorType oper)
{
	switch(oper)
	{
		case OperatorType::ADD_OPERATOR:
			return "+";
			break;
		case OperatorType::SUB_OPERATOR:
			return "-";
			break;
		case OperatorType::MUL_OPERATOR:
			return "*";
			break;
		case OperatorType::DIV_OPERATOR:
			return "/";
			break;
		case OperatorType::LEFT_BRACKETS:
			return "(";
			break;
		case OperatorType::RIGHT_BRACKETS:
			return ")";
			break;
		default:
			return "#";
			break;
	}
}

std::shared_ptr<TokenOperator> OperatorTypeToToken(const OperatorType type)
{
	switch (type)
	{
		case OperatorType::ADD_OPERATOR:
			return std::make_shared<AddOperator>();
			break;
		case OperatorType::SUB_OPERATOR:
			return std::make_shared<SubOperator>();
			break;
		case OperatorType::MUL_OPERATOR:
			return std::make_shared<MulOperator>();
			break;
		case OperatorType::DIV_OPERATOR:
			return std::make_shared<DivOperator>();
			break;
		case OperatorType::LEFT_BRACKETS:
			return std::make_shared<LeftBrackets>();
			break;
		case OperatorType::RIGHT_BRACKETS:
			return std::make_shared<RightBrackets>();
			break;
		default:
			return nullptr;
	}
}

TokenPtrVec CParser::parse(const std::string &s)
{
	TokenPtrVec result;
	auto count = s.size();

	std::string strNumber;
	std::string strOperator;
	//添加(
	retult.push_back(std::make_shared<LeftBrackets>());

	//逐字符分析传入的string 
	//如果是数字或者. 将其作为TokenNumber加入到result
	//如果是operator 将其作为TokenOperator加入到result				
	for (decltype(count)index = 0; index < count; index++) {
		if (isalnum(s[index]) || s[index] == '.') {
			if (strOperator.length() > 0)  {
				for (std::size_t i = 0; i < strOperator.length(); i++) {
					auto operaType = StrToOperator(strOperator[i]);
					auto token = OperatorTypeToToken(operaType);
					if (nullptr != token)  {
						retult.push_back(token);
					}
				}
				strOperator.clear();
			}
			strNumber += s[inded];
		} else {
			if (strNumber.length() > 0)  {
				auto number = std::make_shared<TokenNumber>(strNumber);
				result.push_back(number);
				strNumber.clear();
			}
			strOperator += s[index];
		}	
	}
	if (strNumber.length() > 0)  {
		auto number = std::make_shared<TokenNumber>(strNumber);
		retult.push_back(number);
		strNumber.clear();
	}

	//添加)
	result.push_back(std::make_shared<RightBrackets>());
	return result;
}

struct OperatorPrioityPair
{
	OperatorPrioity left;
	OperatorPrioity right;

	OperatorPrioityPair(OperatorPrioity left, OperatorPrioity right)
	{
		this->left = left;
		this->right = right;
	}

	bool operator<(const OperatorPrioityPair &rhs) const
	{
		if (this->left != rhs.left)  {
			return this->lefr < rhs.left;
		} 
		if (this->right != rhs.right) {
			return this->right < rhs.right;
		}

		return false;
	}
};

enum class CompareResult
{
	ERROR,
	LEFT_HIGHER,
	EQUAL,
	RIGHT_HIGHER,
};

const static std::map<OperatorPrioityPair, CompareResult> operatorPriorityMap = {
	{{OperatorPrioity::ADD_LEVEL,OperatorPrioity::ADD_LEVEL}, CompareResult::LEFT_HIGHER},
	{{OperatorPrioity::ADD_LEVEL,OperatorPrioity::MUL_LEVEL}, CompareResult::RIGHT_HIGHER},
	{{OperatorPrioity::ADD_LEVEL,OperatorPrioity::LEFT_BRACKETS_LEVEL}, CompareResult::RIGHT_HIGHER},
	{{OperatorPrioity::ADD_LEVEL,OperatorPrioity::RIGHT_BRACKETS_LEVEL}, CompareResult::LEFT_HIGHER},
	
	{{OperatorPrioity::MUL_LEVEL,OperatorPrioity::ADD_LEVEL}, CompareResult::LEFT_HIGHER},
	{{OperatorPrioity::MUL_LEVEL,OperatorPrioity::MUL_LEVEL}, CompareResult::LEFT_HIGHER},
	{{OperatorPrioity::MUL_LEVEL,OperatorPrioity::LEFT_BRACKETS_LEVEL}, CompareResult::RIGHT_HIGHER},
	{{OperatorPrioity::MUL_LEVEL,OperatorPrioity::RIGHT_BRACKETS_LEVEL}, CompareResult::LEFT_HIGHER},

	{{OperatorPrioity::LEFT_BRACKETS_LEVEL,OperatorPrioity::ADD_LEVEL}, CompareResult::RIGHT_HIGHER},
	{{OperatorPrioity::LEFT_BRACKETS_LEVEL,OperatorPrioity::MUL_LEVEL}, CompareResult::RIGHT_HIGHER},
	{{OperatorPrioity::LEFT_BRACKETS_LEVEL,OperatorPrioity::LEFT_BRACKETS_LEVEL}, CompareResult::RIGHT_HIGHER},
	{{OperatorPrioity::LEFT_BRACKETS_LEVEL,OperatorPrioity::RIGHT_BRACKETS_LEVEL}, CompareResult::EQUAL},

	{{OperatorPrioity::RIGHT_BRACKETS_LEVEL,OperatorPrioity::ADD_LEVEL}, CompareResult::LEFT_HIGHER},
	{{OperatorPrioity::RIGHT_BRACKETS_LEVEL,OperatorPrioity::MUL_LEVEL}, CompareResult::LEFT_HIGHER},
	{{OperatorPrioity::RIGHT_BRACKETS_LEVEL,OperatorPrioity::LEFT_BRACKETS_LEVEL}, CompareResult::ERROR},
	{{OperatorPrioity::RIGHT_BRACKETS_LEVEL,OperatorPrioity::RIGHT_BRACKETS_LEVEL}, CompareResult::LEFT_HIGHER},
};

TokenPtrVec SimpleTokens(const TokenPtrVec &tokens)
{
	TokenPtrVec result;
	auto nCount = tokens.size();

	if (nCount >= 3)  {
		for (std::size_t i = 1; i < nCount; i++) {
			if (TokenType::NUMBER == tokens[i]->getTokenType())  {
				auto left = dynamic_cast<TokenOperator*>(tokens[i-1].get());
				auto right = dynamic_cast<TokenOperator*>(tokens[i+1].get());

				if ((left && OperatorType::LEFT_BRACKETS == left->getOperatorType()) 
					&& (right && OperatorType::RIGHT_BRACKETS == right->getOperatorType()))  {
					for(std::size_t index = 0; index < i-1; index++) {
						result.push_back(tokens[index]);
					}
					result.push_back(tokens[i]);
					
					for (std::size_t index = i+2; index<nCount; index++) {
						result.push_back(tokens[index]);
					}
					return result;
				}	
			}
		}
	}
	return tokens;
}

TokenPtr CParser::Calculate(TokenPtrVec tokens)
{
	do {
		auto resultTokens = SimpleTokens(tokens);
		if (resultTokens.size() == tokens.size())  {
			break;
		}else {
			tokens=std::move(resultTokens);
		}
	} while (true);

	if (tokens.size() == 1)  {
		return tokens[0];
	}else {
		int arrayIndex[5]={0};
		bool notComputed = true;
		TokenOperator *left = nullptr;
		TokenOperator *mid = nullptr;
		TokenOperator *right = nullptr;
		while (tokens.size() >= 5 && notComputed) {
			right = dynamic_cast<TokenOperator*>(token[arrayIndex[4]].get());
			while (!left || !mid || !right) {
				if (right)  {
					left = mid;
					arrayIndex[0] = arrayIndex[2];
					mid = right;
					arrayIndex[2] = arrayIndex[4];
				}
				arrayIndex[4] ++;
				right = dynamic_cast<TokenOperator*>(token[arrayindex[4]].get());
			}
			while (true) {
			
			}
		}
	}
}
} /* namespace calculater */
