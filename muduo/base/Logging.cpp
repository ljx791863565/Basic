#include "Logging.h"

#include "CurrentThread.h"
#include "Timestamp.h"
#include "TimeZone.h"

#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <sstream>

namespace muduo {

/*
 * __thread是GCC内置的线程局部存储设施，存取效率可以和全局变量相比。
 * __thread变量每一个线程有一份独立实体，各个线程的值互不干扰。
 * 可以用来修饰那些带有全局性且值可能变，但是又不值得用全局变量保护的变量。
 *   __thread使用规则：
 *   只能修饰POD类型(类似整型指针的标量，不带自定义的构造、拷贝、赋值、析构的类型，二进制内容可以任意复制memset,memcpy,且内容可以复原)
 *   不能修饰class类型，因为无法自动调用构造函数和析构函数，
 *   可以用于修饰全局变量，函数内的静态变量，
 *   不能修饰函数的局部变量或者class的普通成员变量，
 *   且__thread变量值只能初始化为编译器常量(值在编译器就可以确定const int i=5,运行期常量是运行初始化后不再改变const int i=rand()).
 */
__thread char t_errnobuf[512];
__thread char t_time[64];
__thread time_t t_lastSecond;

const char *strerror_tl(int savedErrno)
{
	return strerror_r(savedErrno, t_errnobuf, sizeof(t_errnobuf));
}

Logger::LogLevel initLogLevel()
{
	if (::getenv("MUDUO_LOG_TRACE"))  {
		return Logger::TRACE;
	} else if (::getenv("MUDUO_LOG_DEBUG")) {
		return Logger::DEBUG;
	} else {
		return Logger::INFO;
	}
}	

Logger::LogLevel g_logLevle = initLogLevel();

const char *LogLevleName[Logger::NUM_LOG_LEVELS] = 
{
	"TRACE",
	"DEBUG",
	"INFO",
	"WARN",
	"ERROR",
	"FATAL",
};

class T
{
public:
	T(const char *str, unsigned len)
		:str_(str), len_(len)
	{
		assert(strlen(str) == len_);
	}

	const char *str_;
	const unsigned len_;
};

inline LogStream& operator<<(LogStream& s, T v)
{
	s.append(v.str_, v.len_);
	return s;
}

inline LogStream& operator<<(LogStream& s, const Logger::SourceFile& f)
{
	s.append(f.data_, f.size_);
	return s;
}

void defaultOutput(const char *msg, int len)
{
	size_t n = fwrite(msg, 1, len, stdout);
	//FIXME check n ...
}

void defaultFlush()
{
	fflush(stdout);
}
Logger::OutPutFunc g_output = defaultOutput;
Logger::FlushFunc g_flush = defaultFlush;
TimeZone g_logTimeZone;
} /* namespace muduo */

using namespace std;

Logger::Impl::Impl(LogLevel level, int savedErrno, const SourceFile& file, int line)
	:time_(Timestamp::now()), stream_(), level_(level), line_(line), basename_(file)
{
	formatTime();	
}
