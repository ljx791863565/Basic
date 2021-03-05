#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <iostream>
#include <pthread.h>
#include <queue>

#include <errno.h>
#include <sys/types.h>

typedef struct worker
{
	void *(process)(void);
	void *arg;
	struct worker *next;
}Thread_Worker;

class ThreadPool
{
public:
	ThreadPool(int n)
		:max_thread_num(n)
	{
		
	}

private:
	pthread_mutex_t	lock;
	pthread_cond_t	ready_cond;
	Thread_Worker	*head;
	int				shutdown;
	pthread_t		*thread_id;
	const int		max_thread_num;
	int				cur_size;
};
#endif /* end of :__THREAD_POOL_H__ */
