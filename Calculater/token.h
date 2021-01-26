#ifndef TOKEN_H_
#define TOKEN_H_

#include "calc_type_define.h"
#include <string>

namespace calculater {
class CToken
{
public:
	virtual TokenType getTokenType()=0;
	virtual std::string toString()=0;
	virtual  ~CToken()
	{}
};
} /* namespace calculater */
#endif /* end of :TOKEN_H_ */
