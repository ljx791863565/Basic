#ifndef OS_H
#define OS_H

// 这里作为不同系统一些常用函数封装 

#ifdef OS_NO_C_LIB_DEFINES
void* os_malloc(size_t size);
void os_free(void *ptr);
#else
#ifndef os_malloc
#define os_malloc(n) malloc(n)
#endif 

#ifndef os_free
#define os_free(p) free(p)
#endif 
#endif

typedef long os_time_t;

void os_sleep(os_time_t sec, os_time_t usec);

struct os_time {
    os_time_t sec;
    os_time_t usec;
};

struct os_reltime {
    os_time_t sec;
    os_time_t usec;
};

// get current time
int os_get_time(struct os_time *t);

// get relative time 
int os_get_reltime(struct os_reltime *s);

#endif //OS_H