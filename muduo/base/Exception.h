#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "Types.h"
#include <exception>

namespace muduo {
class Exception: public std::exception
{
public:
	Exception(string msg);
	~Exception() noexcept override = default;
	const char *what() const noexcept override 
	{
		return message_.c_str();
	}
	const char *stackTrace() const noexcept
	{
		return stack_.c_str();
	}
private:
	string message_;
	string stack_;
};
} /* namespace muduo */
#endif /* end of :EXCEPTION_H */