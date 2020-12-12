#ifndef MUDUO_BASE_COPYABLE_H
#define MUDUO_BASE_COPYABLE_H

//一个空基类 用于标记(tag)值类型
namespace muduo {
class Copyable
{
protected:
	Copyable() = default;
	~Copyable() = default;
};
} /* namespace muduo */
#endif /* end of :MUDUO_BASE_COPYABLE_H */
