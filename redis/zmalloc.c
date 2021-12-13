#include "zmalloc.h"
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define PREFIX_SIZE (sizeof(size_t))

static size_t used_memory = 0;
static int zmalloc_thread_safe = 0;
static pthread_mutex_t zmalloc_used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;

#define update_zmalloc_stat_add(__n) do {				\
	pthread_mutex_lock(&zmalloc_used_memory_mutex);		\
	used_memory += (__n);						\
	pthread_mutex_unlock(&zmalloc_used_memory_mutex);	\
} while(0)

#define update_zmalloc_stat_sub(__n) do {				\
	pthread_mutex_lock(&zmalloc_used_memory_mutex);		\
	used_memory -= (__n);						\
	pthread_mutex_unlock(&zmalloc_used_memory_mutex);	\
} while(0)

#define update_zmalloc_stat_alloc(__n) do {			\
	size_t _n = (__n);									\
	if (_n&(sizeof(long)-1)) {							\
		_n += sizeof(long) - (_n&(sizeof(long)-1));		\
	}													\
	if (zmalloc_thread_safe) {							\
		update_zmalloc_stat_add(_n);					\
	} else {											\
		used_memory += _n;						\
	}													\
} while(0)

#define update_zmalloc_stat_free(__n) do {				\
	size_t _n = (__n);									\
	if (_n&(sizeof(long)-1)) {							\
		_n += sizeof(long) - (_n&(sizeof(long)-1));		\
	}													\
	if (zmalloc_thread_safe) {							\
		update_zmalloc_stat_sub(_n);					\
	} else {											\
		used_memory -= _n;						\
	}													\
} while(0)

static void zmalloc_default_oom(size_t size)
{
	fprintf(stderr, "zmalloc Out Of Menory trying to allocate %zu bytes\n", size);
	// FIXED :这里的about是否有更好的替换 
	fflush(stderr);
	abort();
}

static void (*zmalloc_oom_handler)(size_t) = zmalloc_default_oom;

void zmalloc_enable_thread_safeness(void)
{
	zmalloc_thread_safe = 1;
}

void *zmalloc(size_t size)
{
	void *ptr = malloc(size + PREFIX_SIZE);
	if (!ptr)  {
		zmalloc_oom_handler(size);
	}
	*((size_t*)ptr) = size;
	update_zmalloc_stat_alloc(size + PREFIX_SIZE);
	printf("size = %lu PREFIX_SIZE = %lu used_memory = %lu ptr = %p\n", size, PREFIX_SIZE, used_memory, ptr);
	return (char *)ptr + PREFIX_SIZE;
}

void zmalloc_set_oom_handler(void (*oom_handler)(size_t))
{
	zmalloc_oom_handler = oom_handler;
}

void *zcalloc(size_t size)
{
	void *ptr = calloc(1, size + PREFIX_SIZE);
	if (!ptr)  {
		zmalloc_oom_handler(size);
	}
	*((size_t*)ptr) = size;
	update_zmalloc_stat_alloc(size + PREFIX_SIZE);
	printf("size = %lu PREFIX_SIZE = %lu used_memory = %lu ptr = %p\n", size, PREFIX_SIZE, used_memory, ptr);
	return (char *)ptr + PREFIX_SIZE;
}

void *zrealloc(void *ptr, size_t size)
{
	void *realPtr;
	size_t oldSize;
	void *newPtr;
	if (!ptr)  {
		return zmalloc(size);
	}
	realPtr = (char *)ptr - PREFIX_SIZE;
	oldSize = *((size_t *)realPtr);
	newPtr = realloc(realPtr, size + PREFIX_SIZE);
	if (!newPtr) {
		zmalloc_oom_handler(size);
	}
	*((size_t *)newPtr) = size;
	update_zmalloc_stat_free(oldSize);
	update_zmalloc_stat_alloc(size);

	return (char *)newPtr + PREFIX_SIZE;
}

void zfree(void *ptr)
{
	void *realPtr = NULL;
	size_t oldSize = 0;
	if (ptr == NULL) {
		return ;
	}
	realPtr = (char *)ptr - PREFIX_SIZE;
	oldSize = *((size_t *)realPtr);
	update_zmalloc_stat_free(oldsize + PREFIX_SIZE);
	printf("size = %lu PREFIX_SIZE = %lu used_memory = %lu ptr = %p\n", oldSize, PREFIX_SIZE, used_memory, ptr);
	free(realPtr);
}

size_t zmalloc_used_memory(void)
{
	return used_memory;
}
