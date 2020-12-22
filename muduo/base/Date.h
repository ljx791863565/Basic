#ifndef DATE_H
#define DATE_H


//时间类
#include "Copyable.h"
#include "Types.h"

struct tm;
namespace muduo {
class Date : public muduo::Copyable
{
public:
	struct YearMonthDay
	{
		int year;
		int month;
		int day;
	};
	//每周天数 static const类型 整个类只有一份且共享给每一个类的实例
	static const int kDaysPerWeek = 7;
	static const int kJulianDayOf1970_01_01;

	Date(int year, int month, int day);

	explicit Date(const struct tm&);
	explicit Date(int julianDayNum)
		: julianDayNumber_(julianDayNum)
	{}
	Date()
		:julianDayNumber_(0)
	{}

	void swap(Date &d)
	{
		std::swap(julianDayNumber_, d.julianDayNumber_);
	}

	bool valid() const
	{
		return julianDayNumber_ > 0;
	}

	string toIsoString() const;

	struct YearMonthDay yearMonthDay() const;

	int year() const
	{
		return yearMonthDay().year;
	}

	int month() const
	{
		return yearMonthDay().month;
	}

	int day() const
	{
		return yearMonthDay().day;
	}

	// [ 0 , 1, .., 6 ] ==> [ sunday, monday, ..., saturday ]
	int weekDay() const
	{
		return (julianDayNumber_+1) % kDaysPerWeek;
	}

	int julianDayNumber() const 
	{
		return julianDayNumber_;
	}

private:
	//ulian day 儒略日（公元前4713年1月1日）
	int julianDayNumber_;
};

inline bool operator<(Date x, Date y)
{
	return x.julianDayNumber() < y.julianDayNumber();
}

inline bool operator==(Date x, Date y)
{
	return x.julianDayNumber() == y.julianDayNumber();
}

} /* namespace muduo */
#endif /* end of :DATE_H */
