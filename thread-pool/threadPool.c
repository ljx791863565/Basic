#include "threadPool.h"

CThread_Pool *pool = NULL;

void pool_init(int max_thread_num)
{
	pool = (CThread_Pool *)malloc(sizeof(CThread_Pool));
	if (pool == NULL) {
		debug(LOG_ERR, "%s", "malloc() error");
		exit(0);
	}
	pthread_mutex_init(&(pool->queue_lock), NULL);
	pthread_cond_init(&(pool->queue_ready), NULL);

	pool->queue_head = NULL;
	pool->max_thread_num = max_thread_num;
	pool->cur_queue_size = 0;

	pool->shutdown = 0;
	
	pool->thread_id = (pthread_t *)malloc(max_thread_num * sizeof(pthread_t));

	for(int i = 0; i < pool->max_thread_num; i++) {
		int ret = pthread_create(&(pool->thread_id[i]), NULL, thread_routine, NULL);
		if (ret < 0) {
			debug(LOG_ERR, "%s", "pthread_create error");
			exit(0);
		}
	}
	debug(LOG_INFO, "%s", "pthread pool working");
}

int pool_add_worker(void *(*process)(void *arg), void *arg)
{
	CThread_Worker *new_worker = (CThread_Worker *)malloc(sizeof(CThread_Worker));
	new_worker->process = process;
	new_worker->arg = arg;
	new_worker->next = NULL;

	pthread_mutex_lock(&(pool->queue_lock));
	CThread_Worker *member = pool->queue_head;
	if (member != NULL) {
		while (member->next != NULL) {
			member = member->next;
		}
		member->next = new_worker;
	}else {
		pool->queue_head = new_worker;
	}

	pool->cur_queue_size++;
	pthread_mutex_unlock(&(pool->queue_lock));
	pthread_cond_signal(&(pool->queue_ready));

	return 0;
}

int pool_destroy()
{
	if (pool->shutdown != 0) {
		debug(LOG_INFO, "%s", "thread is not working");
		return -1;
	}
	pool->shutdown = 1;
	debug(LOG_INFO, "%s", "thread pool well be destory");
	pthread_cond_broadcast(&(pool->queue_ready));

	for(int i = 0; i < pool->max_thread_num; i++) {
		pthread_join(pool->thread_id[i], NULL);
	}
	free(pool->thread_id);

	CThread_Worker *head = NULL;
	while (pool->queue_head != NULL) {
		head = pool->queue_head;
		free(head);
		pool->queue_head = pool->queue_head->next;
	}

	pthread_mutex_destroy(&(pool->queue_lock));
	pthread_cond_destroy(&(pool->queue_ready));

	free(pool);
	pool = NULL;
	return 0;
}

void *thread_routine(void *arg)
{
	debug(LOG_INFO, "starting thread 0x%x", (unsigned int)pthread_self());

	while (1) {
		pthread_mutex_lock(&(pool->queue_lock));
		while (pool->cur_queue_size == 0 && pool->shutdown == 0) {
			debug(LOG_INFO, "thread 0x%x is waiting", (unsigned int)pthread_self());
			pthread_cond_wait(&(pool->queue_ready), &(pool->queue_lock));
		}

		if (pool->shutdown != 0) {
			pthread_mutex_unlock(&(pool->queue_lock));
			debug(LOG_INFO, "thread 0x%x will exit", (unsigned int)pthread_self());
			pthread_exit(NULL);
		}

		debug(LOG_INFO, "thread 0x%x is starting to working", (unsigned int)pthread_self());

		pool->cur_queue_size--;
		CThread_Worker *worker = pool->queue_head;
		pool->queue_head = worker->next;
		pthread_mutex_unlock(&(pool->queue_lock));

		//调用
		(*(worker->process))(worker->arg);
		free(worker);
		worker = NULL;
	}
}


