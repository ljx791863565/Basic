#ifndef _ZMALLOC_H_
#define _ZMALLOC_H_

#define __xstr(s) __str(s)
#define __str(s) #s


#ifndef ZMALLOC_LIB 
#define ZMALLOC_LIB "libc"
#endif 

#include <stdio.h>
#include <stdlib.h>
void *zmalloc(size_t size);
void *zcalloc(size_t size);
void *zrealloc(void *ptr, size_t size);
void zfree(void *ptr);
void zmalloc_enable_thread_safeness(void);
size_t zmalloc_used_memory(void);
void zmalloc_set_oom_handler(void (*oom_handler)(size_t));

#endif /* end of :_ZMALLOC_H_ */
