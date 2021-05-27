#include <iostream>

namespace LJX {

// 基础的迭代器类
template <typename T>
class Iterator {
public:
	using value_type = T;
	using size_type = size_t;
public:
	// 构造传入三个参数 迭代次数 初始值 步长 
	Iterator(size_type cur_start, value_type begin_val, value_type step_val)
		:cursor_(cur_start), step_(step_val), value_(begin_val)
	{
		value_ += (step_ * cursor_);
	}

	// 类似*it取得迭代器指向的值
	value_type operator*() const 
	{
		return value_;
	}

	// 实现类似it != end() 的操作
	bool operator!=(const Iterator &rhs) const 
	{
		return (cursor_ != rhs.cursor_);
	}

	// 实现类似 ++it 
	Iterator &operator++(void)
	{
		value_ += step_;
		++cursor_;
		return  *this;
	}

private:
	size_type cursor_;					// 迭代次数 不为负数 最大值类似begin到end长度
	const value_type step_;				// 步长
	value_type value_;					// 值
};

template <typename T>
class Impl {
public:

private:

};
} // LJX 
