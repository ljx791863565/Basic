/* $Id: debug.c 1305 2007-11-01 20:04:20Z benoitg $ */
/** @file debug.c
    @brief Debug output routines
    @author Copyright (C) 2004 Philippe April <papril777@yahoo.com>
*/


#include "debug.h"
static void write_data_to_file(const char *path, char *str)
{
	FILE *fp = fopen(path, "a+");
	if (fp == NULL) {
		fprintf(stderr, "%s\n", "fd is NULL and file is not open");
		return;
	}
	if (str && str[0] != '\0') {
		fwrite(str, strlen(str), 1, fp);
		char *pNULL = "\n";
		fwrite(pNULL, strlen(pNULL), 1, fp);
	}
	fclose(fp);
}

static void getNowString(const char *format, char *output, size_t optlen)
{
	memset(output, 0, optlen);
	time_t now;
	time(&now);
	//C 库函数 size_t strftime(char *str, size_t maxsize, const char *format, const struct tm *timeptr) 
	//根据 format 中定义的格式化规则，格式化结构 timeptr 表示的时间，并把它存储在 str 中。
	strftime(output, optlen, format, localtime(&now));
}
/** @internal
Do not use directly, use the debug macro */
void _debug(const char *filename, int line, int level, const char *format, ...)
{
    char buf[28];
    va_list vlist;
    time_t ts;

    time(&ts);
	va_start(vlist, format);
	char temp1[MAXBUF] = {0}, temp2[MAXBUF] = {0};
	if (level <= LOG_WARNING) {
		fprintf(stderr, "[%d][%.24s][%u](%s:%d) ", level, ctime_r(&ts, buf), getpid(),
				filename, line);
		fprintf(temp1, "[%d][%.24s][%u](%s:%d) ", level, ctime_r(&ts, buf), getpid(),
				filename, line);
		vfprintf(stderr, format, vlist);
		va_list args;
		va_start(args, format);
		vsprintf(temp2, format, args);
		va_end(args);
		fputc('\n', stderr);
		printf("%s", temp1);
	}else {
		fprintf(stdout, "[%d][%.24s][%u](%s:%d) ", level, ctime_r(&ts, buf), getpid(),
				filename, line);
		fprintf(temp1, "[%d][%.24s][%u](%s:%d) ", level, ctime_r(&ts, buf), getpid(),
				filename, line);
		vfprintf(stdout, format, vlist);
		va_list args;
		va_start(args, format);
		vsprintf(temp2, format, args);
		va_end(args);
		fputc('\n', stdout);
		fflush(stdout);
		printf("%s", temp2);
	}

	char temp3[2*MAXBUF] = {0};
	if (strlen(temp1) > 0 || strlen(temp2) > 0) {
		sprintf(temp3, "%s %s", temp1, temp2);
		write_data_to_file(LOG_FILE_NAME, temp3);
	}
}

