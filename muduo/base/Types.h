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
//仅仅引用std::string而不是全部的std 尽量减少std对公共空间的污染
//这个using表明只在引用了这个头文件和muduo类中可以直接使用string省略掉std::string
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
