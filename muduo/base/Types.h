#ifndef MUDUO_TYPES_H
#define MUDUO_TYPES_H

//基本类型声明 包括muduo::string
#include <stdint.h>
#include <string.h>
#include <string>

#ifndef NDEBUG
#include <assert.h>
#endif

namespace muduo {
using std::string;

inline void memZero(void *p, size_t n)
{
	memset(p, 0, n);
}

template <typename To, typename From>
inline To implicit_cast(const From &f)
{
	return f;
}

template <typename To, typename From>
inline To down_cast(From *f)
{
	//else if永远不会执行 一般在调试中使用
	if (false)  {
		implicit_cast<From*, To>(0);
	}

#if !defined(NDEBUG) && !defined(GOOGLE_PROTOBUF_NO_RTTI)
	assert(f == NULL || dynamic_cast<To>(f) != NULL);
#endif
	return static_cast<To>(f);
}
} /* namespace muduo */
#endif /* end of :MUDUO_TYPES_H */
