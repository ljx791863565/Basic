#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <errno.h>
#include "debug.h"
typedef struct worker
{
	void *(*process)(void *arg);
	void *arg;
	struct worker *next;
}CThread_Worker;

typedef struct pool
{
	pthread_mutex_t queue_lock;
	pthread_cond_t queue_ready;
	CThread_Worker *queue_head;
	
	int shutdown;
	pthread_t *thread_id;
	int max_thread_num;	
	int cur_queue_size;
}CThread_Pool;


int pool_add_worker(void*(*process)(void *arg), void *arg);
void pool_init(int max_thread_num);
int pool_destory();
void *thread_routine(void *arg);
#endif //__THREAD_POOL_H__

