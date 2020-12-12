#ifndef LOGSTREAM_H
#define LOGSTREAM_H

#include "Noncopyable.h"
#include "StringPiece.h"
#include "Types.h"
#include <assert.h>
#include <string.h>

namespace muduo {
namespace detail {

const int kSmallBuffer = 4000;
const int kLargeBuffer = 4000 * 1000;

template <int SIZE>
class FixedBuffer : Noncopyable
{
public:
	FixedBuffer()
		:cur_(data_)
	{
		SetCookie(cookieStart);
	}

	~FixedBuffer()
	{
		SetCookie(cookieEnd);
	}

	void SetCookie(void (*cookie)())
	{
		return cookie_ = cookie;
	}
	
	void append(const char *buf, size_t len)
	{
		if (implicit_cast<size_t>(avail()) > len)  {
			memcpy(cur_, buf, len);
			cur_ += len;
		}
	}

	int avail() const
	{
		return static_cast<int> (end() - cur_);
	}

	const char *data() const 
	{
		return data_;
	}

	int length() const 
	{
		return static_cast<int>(cur_ - data_);
	}

	//这个指针需要支持修改 不能const
	char *current()
	{
		return cur_;
	}

	void add(size_t len)
	{
		cur_ += len;
	}

	void reser()
	{
		cur_ = data_;
	}

	void bzero()
	{
		memZero(data_, sizeof data_);
	}

	const char *debugString();

	string toString() const
	{
		return string(data_, length());
	}

	StringPiece toStringPiece() const
	{
		return StringPiece(data_, length());
	}
private:
	const char *end() const
	{
		reurn data_ + sizeof data_;
	}
	static void cookieStart();
	static void cookieEnd();

	void (*cookie_)();
	char *cur;
	char data_[SIZE];
};
} /* namespace detail */

class LogStream : Noncopyable
{
	using LosStream = self;
public:
	using detail:FixedBuffer<detail::kSmallBuffer> = Buffer;

	self& operator<<(bool v)
	{
		buffer_.append(v ? "1" : "0", 1);
		return *this;
	}

	self& operator<<(short);
	self& operator<<(unsigned short);
	self& operator<<(int);
	self& operator<<(unsigned int);
	self& operator<<(long);
	self& operator<<(unsigned long);
	self& operator<<(long long);
	self& operator<<(unsigned long long);
	self& operator<<(const void *);
	self& operator<<(double);

	self& operator<<(float v)
	{
		*this << static_cast<double>(v);
		return *this;
	}
	
	self& operator<<(char v)
	{
		buffer_.append(&v, 1);
	}

	self& operator<<(const char *str)
	{
		if (str)  {
			buffer_.append(str, strlen(str));
		}else {
			//为什么是6?
			buffer_.append("(null)", 6);
		}
		return *this;
	}

	self& operator<<(const unsigned char *str)
	{
		return operator<<(reinterpret_cast<const char*>(str)); 
	}

	self& operator<<(const string& s)
	{
		buffer_.append(s.c_str(), s.size());
		return *this;
	}

	self& operator<<(const StringPiece& sp)
	{
		buffer_.append(sp.data(), sp.size());
		return *this;
	}

	self& operator<<(const Buffer& b)
	{
		*this << b.toStringPiece();
		return *this;
	}

	void append(const char *data, int len)
	{
		buffer_.append(data, len);
	}

	const Buffer& buffer() const
	{
		return buffer_;
	}

	void resetBuffer()
	{
		buffer_.reset();
	}

private:
	Buffer buffer_;
	static const int kMaxNumericSize = 32;

	template <typename T>
	void formatInteger(T);

	void staticCheck();
};

class Fmt
{
public:
	template <typename T>
	Fmt(const char *fmt, T val);

	const char *data() const
	{
		return buf_;
	}

	int length() const
	{
		return length_;
	}
private:
	char buf_[32];
	int length_;
};

inline LogStream& operator<<(LogStream &s, const Fmt &fmt)
{
	s.append(fmt.data(), fmt.length());
	return s;
}

/*
 * 国际单位制(法语:Système International d'Unités 符号:SI)
 * 1K = 1000
 */
string formatSI(int64_t n);

/*
 * (IEC)binary  1Ki = 1024
 */
string formatIEC(int64_t n);

} /* namespace muduo */
#endif /* end of :LOGSTREAM_H */
