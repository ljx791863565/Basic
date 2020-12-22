#ifndef MUDUO_STRING_PIEXE_H
#define MUDUO_STRING_PIEXE_H

#include <string.h>
#include <iosfwd>
#include "Types.h"

namespace muduo {
class StringArg
{
public:
	StringArg(const char *str)
		: str_(str)
	{}
	StringArg(const StringArg &s)
		:str_(s.c_str())
	{}
	const char *c_str() const
	{
		return str_;
	}
private:
	const char *str_;
};

class StringPiece {
public:
	StringPiece ()
		:ptr_(NULL), length_(0)
	{}
	StringPiece(const char *str)
		:ptr_(str), length_(static_cast<int>(strlen(ptr_)))
	{}
	StringPiece(const unsigned char *str)
		:ptr_(reinterpret_cast<const char *>(str)), length_(static_cast<int>(strlen(ptr_)))
	{}
	StringPiece(const std::string& s)
		:ptr_(s.data()), length_(static_cast<int>(s.size()))
	{}
	StringPiece(const char *offset, int len)
		:ptr_(offset), length_(len)
	{}

	const char *data() const
	{
		return ptr_;
	}

	int size() const
	{
		return length_;
	}
	
	bool empty() const
	{
		return length_ == 0;
	}

	const char *begin() const 
	{
		return ptr_;
	}

	const char *end() const
	{
		return ptr_ + length_;
	}

	void clear()
	{
		ptr_ = NULL;
		length_ = 0;
	}

	void set(const char *buffer, int len)
	{
		ptr_ = buffer;
		length_ = len;
	}

	void set(const char *str)
	{
		ptr_ = str;
		length_ = static_cast<int>(strlen(str));
	}

	void set(const void *buffer, int len)
	{
		ptr_ = reinterpret_cast<const char*>(buffer);
		length_ = len;
	}
	
	char operator[](int i) const
	{
		return ptr_[i];
	}

	void remove_prefix(int n)
	{
		ptr_ += n;
		length_ -= n;
	}

	void remove_suffix(int n)
	{
		length_ -= n;
	}

	bool operator==(const StringPiece &s) const
	{
		return (length_ == s.length_) && (memcmp(ptr_, s.ptr_, length_) == 0);
	}

	bool operator!=(const StringPiece &s) const
	{
		return !(*this == s);
	}

#define STRINGPIECE_BINARY_PREDICATE(cmp, auxcmp)				\
	bool operator cmp(const StringPiece &s) const {				\
		int r = memcmp(ptr_, s.ptr_, length_ < s.length_ ? length_ : s.length_); \
		return ((r auxcmp 0) || ((r == 0) && (length_ cmp s.length_)));			\
	}
	STRINGPIECE_BINARY_PREDICATE(<, <);
	STRINGPIECE_BINARY_PREDICATE(<=, <);
	STRINGPIECE_BINARY_PREDICATE(>=, >);
	STRINGPIECE_BINARY_PREDICATE(>, >);
#undef STRINGPIECE_BINARY_PREDICATE

	int compare(const StringPiece &s) const
	{
		int r = memcmp(ptr_, s.ptr_, length_ < s.length_ ? length_ : s.length_);
		if (r == 0)  {
			if (length_ < s.length_)  {
				r = -1;
			}else if (length_ > s.length_)  {
				r = 1;
			}
		}
		return r;
	}

	std::string as_string() const
	{
		return std::string(data(), size());
	}

	// 先将原字符串清空，然后赋予新的值作替换
	void CopyToString(std::string *target) const
	{
		target->assign(ptr_, length_);
	}

	bool starts_with(const StringPiece &s) const
	{
		return ((length_ >= s.length_) && (memcmp(ptr_, s.ptr_, s.length_) == 0));
	}
private:
	const char *ptr_;
	int	length_;
};

#ifdef HAVE_TYPE_TRAITS
template<> struct __type_treits<muduo::StringPiece> 
{
	typedef __true_type		has_trivial_default_constructor;
	typedef __true_type		has_trivial_copy_constructor;
	typedef __true_type		has_trivial_assignment_operator;
	typedef __true_type		has_trivial_destructor;
	typedef __true_type		is_POD_type;
};
#endif

std::ostream& operator<<(std::ostream& o, const muduo::StringPiece &piece);

} /* namespace nuduo */
#endif /* end of :MUDUO_STRING_PIEXE_H */
