#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <stdio.h>
#include <errno.h>
#include <syslog.h>
#include <stdarg.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#define MAXBUF 10240
#define LOG_FILE_NAME "/mnt/debug.log"

#define debug(level, format...) _debug(__FILE__, __LINE__, level, format)

void _debug(const char *filename, int line, int level, const char *format, ...);
 
#endif //__DEBUG_H__
