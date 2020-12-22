#ifndef TIMEZONE_H
#define TIMEZONE_H

#include "Copyable.h"

#include <memory.h>
#include <time.h>

namespace muduo {
class TimeZone : public muduo:Copyable
{
public:
	explicit TimeZone(const char *zonefile);
	TimeZone(int eastOfUtc, const char *tzname);
	TimeZone() = default;

	bool valid() const
	{
		return static_cast<bool>(data_);
	}

	// GMT：Greenwich Mean Time 格林尼治标准时间。
	// 这是以英国格林尼治天文台观测结果得出的时间，这是英国格林尼治当地时间，这个地方的当地时间过去被当成世界标准的时间
	// UT：Universal Time 世界时。根据原子钟计算出来的时间
	// UTC：Coordinated Universal Time 协调世界时。因为地球自转越来越慢，每年都会比前一年多出零点几秒，
	// 每隔几年协调世界时组织都会给世界时+1秒，让基于原子钟的世界时和基于天文学（人类感知）的格林尼治标准时间相差不至于太大。
	// 并将得到的时间称为UTC，这是现在使用的世界标准时间
	//
	// GMT并不等于UTC，而是等于UTC+0，只是格林尼治刚好在0时区上
	// GMT = UTC+0
	struct tm toLocalTime(time_t secondsSinceEpoch) const;
	time_t fromLocalTime(const struct &tm) const;

	static struct tm toUtcTime(time_t secondsSinceEpoch, bool yday = false);
	static time_t fromUtcTime(const struct &tm);
	static time_t fromUtcTime(int year, int month, int day, int hour, int minute, int seconds);

	struct Data;
private:
	std::shared_ptr<Data> data_;
};
} /* namespace muduo */
#endif /* end of :TIMEZONE_H */
