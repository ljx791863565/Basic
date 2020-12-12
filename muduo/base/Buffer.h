#ifndef MUDUO_BUFFER_H
#define MUDUO_BUFFER_H
#include "Copyable.h"
#include "StringPiece.h"
#include "Types.h"

#include "Endian.h"

#include <algorithm>
#include <vector>

#include <assert.h>
#include <string.h>

namespace muduo {
namespace net {
class Buffer : public muduo::Copyable
{
public:
	static const size_t kCheapPrepend = 8;
	static const size_t kInitialSize = 1024;

	// explicit表示禁止使用经过转换构造函数进行的隐式转换，构造器只能被明确的调用/使用， 不能作为类型转换操作符被隐含的使用
	// 即	Buffer a(xxx);可以
	//		Buffer a = xxx;编译报错
	explicit Buffer(size_t initialSize = kInitialSize)
		:buffer_(kCheapPrepend + initialSize),
		readerIndex_(kCheapPrepend),
		writerIndex_(kCheapPrepend)
	{
		assert(readableBytes() == 0);
		assert(writableBytes() == initialSize);
		assert(prependableBytes() == kCheapPrepend);
	}

	void swap(Buffer &b)
	{
		buffer_.swap(b.buffer_);
		std::swap(readerIndex_, b.readerIndex_);
		std::swap(writerIndex_, b,writerIndex_);
	}

	//已读区间大小
	size_t readableBytes() const
	{
		return writerIndex_ - readerIndex_;
	}

	//剩余可读区间大小
	size_t writableBytes() const
	{
		return buffer_.size() - writerIndex_;
	}

	//保留区间大小
	size_t prependableBytes() const
	{
		return readerIndex_;
	}

	//窥探 获得readerIndex_对应的下标index
	const char *peek() const
	{
		return begin() + readerIndex_;
	}

	int64_t peekInt64() const
	{
		assert(readableBytes() >= sizeof(int64_t));
		int64_t be64 = 0;
		::memcpy(&be64, peek(), sozepf(be64));
		return sockets::networkToHost64(be64);
	}

	int32_t peekInt32() const
	{
		assert(readableBytes() >= sizeof(int32_t));
		int64_t be32 = 0;
		::memcpy(&be32, peek(), sozepf(be32));
		return sockets::networkToHost64(be32);
	}

	int16_t peekInt16() const
	{
		assert(readableBytes() >= sizeof(int16_t));
		int64_t be16 = 0;
		::memcpy(&be16, peek(), sozepf(be16));
		return sockets::networkToHost64(be16);
	}

	int8_t peekInt8() const
	{
		assert(readableBytes() >= sizeof(int8_t));
		int64_t be8 = 0;
		::memcpy(&be8, peek(), sozepf(be8));
		return sockets::networkToHost64(be8);
	}
	//返回可写开始index
	char *beginWrite()
	{
		return begin() + writerIndex_;
	}
	
	const char *beginWrite() const
	{
		return begin() + writerIndex_;
	}

	//填充可写空间
	void hasWritten(size_t len)
	{
		assert(len <= writableBytes());
		writerIndex_ += len;
	}

	void ensureWritableBytes(size_t len)
	{
		//扩容可写空间
		if (writableBytes() < len)  {
			makeSpace(len);
		}
		assert(writableBytes() >= len);
	}

	void unwrite(size_t len)
	{
		assert(len <= readableBytes());
		writerIndex_ -= len;
	}

	const char *findEOL() const
	{
		const void *eol = memchr(peek(), '\n', readableBytes());
		return static_cast<const char*>(eol);
	}

	const char* findEOL(const char *start) const
	{
		assert(peek() <= start);
		assert(start <= beginWrite());
		const void *eol = memchr(start, '\n', beginWrite() - start);
		return static_cast<const char*>(eol);
	}

	const char *findCRLF() const
	{
		const char *crlf = std::search(peek(), beginWrite(), kCRLF, kCRLF+2);
		return crlf == beginWrite() ? NULL : crlf;
	}

	void retrieveInt64()
	{
		retrieve(sizeof(int64_t));
	}

	void retrieveInt32()
	{
		retrieve(sizeof(int32_t));
	}

	void retrieveInt16()
	{
		retrieve(sizeof(int16_t));
	}

	void retrieveInt8()
	{
		retrieve(sizeof(int8_t));
	}

	//重置len长度的可读区间
	void retrieve(size_t len)
	{
		assert(len <= readableBytes());
		if (len < readableBytes())  {
			readerIndex_ += len;
		}else {
			retrieveAll();
		}
	}

	//重置所有读写区间
	void retrieveAll()
	{
		readerIndex_ = kCheapPrepend;
		writerIndex_ = kCheapPrepend;
	}

	//重置readerIndex_到end长度的可读区间
	void retrieveUntil(const char *end)
	{
		assert(peek() <= end);
		assert(end <= beginWrite());
		retrieve(end - peek());
	}

	string retrieveAsString(size_t len)
	{
		assert(len <= readableBytes());
		string result(peek(), len);
		retrieve(len);
		return result;
	}

	string retrieveAllAsString()
	{
		return retrieveAsString(readableBytes());
	}

	StringPiece toStringPiece() const
	{
		return StringPiece(peek(), static_cast<int>(readableBytes()));
	}

	void append(const StringPiece& str)
	{
		append(str.data(), str.size());
	}

	void append(const char *data, size_t len)
	{
		ensureWritableBytes(len);
		std::copy(data, data+len, beginWrite());
		hasWritten(len);
	}
	
	appendInt64(int64_t x)
	{
		int64_t be64 = sockes::hostToNetwork64(x);
		append(&be64, sizeof(be64));
	}

	appendInt32(int32_t x)
	{
		int32_t be32 = sockets::hostToNetwork32(x);
		append(&be32, sizeof(be32));
	}

	appendInt16(int16_t x)
	{
		int16_t be16 = sockets::hostToNetwork16(x);
		append(&be16, sizeof(be16));
	}

	appendInt8(int8_t x)
	{
		int8_t be8 = sockets::hostToNetwork8(x);
		append(&be8, sizeof(be8));
	}

	int64_t readInt64()
	{
		int64_t result = peekInt64();
		retrieveInt64();
		return result;
	}

	int32_t readInt32()
	{
		int32_t result = peekInt32();
		retrieveInt32();
		return result;
	}

	int16_t readInt16()
	{
		int16_t result = peekInt16();
		retrieveInt16();
		return result;
	}

	int8_t readInt8()
	{
		int8_t result = peekInt8();
		retrieveInt8();
		return result;
	}

	void prepend(const void *data, size_t len)
	{
		assert(len <= prependableBytes());
		readerIndex_ -= len;
		const char *d = static_cast<const char*>(data);
		std::copy(d, d + len, begin()+readerIndex_);
	}

	void prependInt64(int64_t x)
	{
		int64_t be64 = sockets::hostToNetwork64(x);
		prepend(&be64, sizeof(be64));
	}

	void prependInt32(int32_t x)
	{
		int32_t be32 = sockets::hostToNetwork32;
		prepend(&be32, sizeof(be32));
	}

	void prependInt16(int16_t x)
	{
		int16_t be16 = sockets::hostToNetwork32(x);
		prepend(&be16, sizeof(be16));
	}

	void prependInt8(int8_t x)
	{
		int8_t be8 = sockets::hostToNetwork8(x);
		prepend(&be8, sizeof(be8));
	}

	void shrink(size_t reserve)
	{
		Buffer other;
		other.ensureWritableBytes(readableBytes() + reserve);
		other.append(toStringPiece());
		swap(other);
	}

	size_t internalCapacity() const
	{
		return buffer_.capacity();
	}

	ssize_t readFd(int fd, int *saveError);
private:
	char *begin()
	{
		return &*buffer_.begin();
	}

	const char *begin() const
	{
		return &*buffer_.begin();
	}

	void makeSpace(size_t len)
	{
		if (writableBytes() + prependableBytes() < len + kCheapPrepend)  {
			buffer_.resize(writerIndex_ + len);
		}else {
			//此处要保证已读标识在保留标识之后
			assert(readerIndex_ > kCheapPrepend);
			size_t readable = readableBytes();
			/*
			 *  //fist [IN]: 要拷贝元素的首地址
			 *  last [IN]:要拷贝元素的最后一个元素的下一个地址
			 *  x [OUT] : 拷贝的目的地的首地址
			 *  
			 *  template<class InIt, class OutIt>
			 *  OutIt copy(InIt first, InIt last, OutIt x);
			 */
			std::copy(begin() + readerIndex_, begin() + writerIndex_, begin() + kCheapPrepend);
			readerIndex_ = kCheapPrepend;
			writerIndex_ = readerIndex_ + readable;
			assert(readable == readableBytes());
		}
	}
private:
	std::vector<char> buffer_;	
	size_t readerIndex_;		//标识已读大小
	size_t writerIndex_;		//标识可读大小
	static const char kCRLF[];
};			   
} /* namespace net */
} /* namespace muduo */
#endif /* end of :MUDUO_BUFFER_H */
