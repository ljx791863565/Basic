#ifndef CURRENT_THREAD_H
#define CURRENT_THREAD_H

#include "Types.h"

namespace muduo {
namespace CurrentThread {
	extern __thread int t_cachedTid;
	extern __thread char t_tidString[32];
	extern __thread int t_tidStringLength;
	extern __thread const char* t_threadName;
	void cachTid();
	inline int tid()
	{
		if (__builtin_expect(t_cachTid == 0, 0))  {
			cachTid();
		}
		return t_cachTid;
	}

	inline const char *tidString()
	{
		return t_tidString;
	}

	inline int tidStringLength()
	{
		return t_tidStringLength;
	}

	inline const char *name()
	{
		return t_threadName;
	}
	
	bool isMainThread();

	void sleepUsec(int64_t demangle);
} /* namespace CurrentThread */
} /* namespace muduo */
#endif /* end of :CURRENT_THREAD_H */
