#ifndef CONDITION_H
#define CONDITION_H

#include "Mutex.h"
#include <pthread.h>

namespace muduo {
class Condition : Noncopyable
{
public:
	explicit Condition(MutexLock& mutex)
		:mutex_(mutex)
	{
		MCHECK(pthread_cond_init(&pcond_, NULL));
	}
private:
	MutexLock& mutex_;
	pthread_cond_t pcond_;
};
} /* namespace muduo */
#endif /* end of :CONDITION_H */
