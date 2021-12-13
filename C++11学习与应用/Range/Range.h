#ifndef RANGE_H
#define RANGE_H 

#include <iostream>
#include <exception>
#include <stdexcept>
namespace range {

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
		// 由步长和迭代次数 可以确定迭代值
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
		return  (*this);
	}

private:
	size_type cursor_;					// 迭代次数 不为负数 最大值类似begin到end长度
	const value_type step_;				// 步长
	value_type value_;					// 值
};

template <typename T>
class Impl {
public:
	using value_type = T;
	using iterator = Iterator<value_type>;
	using const_iterator = const Iterator<value_type>;
	using size_type = typename iterator::size_type;
public:
	Impl(value_type begin_val, value_type end_val,value_type step_val)
		:begin_(begin_val), end_(end_val), step_(step_val), max_count_(get_adjusted_count())
	{}

	size_type size(void) const 
	{
		return max_count_;
	}

	const_iterator begin(void) const 
	{
		return {0, begin_, step_};
	}

	const_iterator end(void) const 
	{
		return { max_count_, begin_, step_ };
	}
private:
	const value_type begin_;
	const value_type end_;
	const value_type step_;	
	const size_type max_count_;

	size_type get_adjusted_count(void) const 
	{
		// 这里考虑可以正向迭代也可以反向迭代
		if (step_ > 0 && begin_ >= end_){
			throw std::logic_error("End value must be greater than begin value.");
		} else if (step_ < 0 && begin_ <= end_) {
			throw std::logic_error("End value must be less than begin value.");
		}

		size_type x = static_cast<size_type>((end_ - begin_) / step_);
		// 这里考虑到x不是完全整除的情况 需要多执行一次迭代
		if ((begin_ + (step_ * x)) != end_) {
			++x;
		}
		return x;
	}
};
} // namespace range 

template <typename T>
range::Impl<T> Range(T end)
{
	return {{}, end, 1};
}

template <typename T>
range::Impl<T> Range(T begin, T end)
{
	return {begin, end, 1};
}

template <typename T, typename U>
auto Range(T begin, T end, U step) -> range::Impl<decltype(begin + step)>
{
	using r_t = range::Impl<decltype(begin + step)>;
	return r_t(begin, end, step);
}
#endif // RANGE_H 
