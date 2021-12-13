#include "includes.h"
#include "os.h"
#include "common.h"

#include <time.h>

void os_sleep(os_time_t sec, os_time_t usec)
{
    if (sec) {
        sleep(sec);
    }
    if (usec) {
        usleep(usec);
    }
}

int os_get_time(struct os_time *t)
{
    struct timeval tv;
    int res = gettimeofday(&tv, NULL);
    t->sec = tv.tv_sec;
    t->usec = tv.tv_usec;

    return res;
}

int os_get_reltime(struct os_reltime *s)
{
    return 0;
}