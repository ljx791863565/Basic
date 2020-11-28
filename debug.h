#ifndef __DEBUG_H__
#define __DEBUG_H__

#define debug(level, format, ...) _debug(__FILE__, __LINE__, level, format, ...)

void _debug(const char *filename, int line, int level, const char *format, ...);
 
#endif //__DEBUG_H__
