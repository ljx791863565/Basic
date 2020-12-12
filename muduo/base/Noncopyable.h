#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace muduo {
class Noncopyable
{
public:
	//delete 表示删除默认构造函数
	Noncopyable(const Noncopyable &) = delete;
	void operator=(const Noncopyable&) = delete;
protected:
	//default表示使用默认构造函数
	Noncopyable() = default;
	~Noncopyable() = default;
};
} /* namespace muduo */
#endif /* end of :NONCOPYABLE_H */
