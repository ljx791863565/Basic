#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include "Copyable.h"
#include "Types.h"

#include <boost/operators.hpp>

namespace muduo {

class Timestamp : public muduo::Copyable,
				  public boost::equality_comparable<Timestamp>,
				  public boost::less_than_comparable<Timestamp>
{
public:
	Timestamp()
		: microSecondsSinceEpoch_(0)
	{}

	explicit Timestamp(int64_t microSecondsSinceEpochArg)
		:microSecondsSinceEpoch_(microSecondsSinceEpochArg)
	{}

	void swap(Timestamp& that)
	{
		std::swap(microSecondsSinceEpoch_, that.microSecondsSinceEpoch_);
	}

	string toString() const;
	string toFormattedString(bool showMicroseconds = true) const;

	bool valid() const 
	{
		return microSecondsSinceEpoch_ > 0;
	}

	int64_t microSecondsSinceEpoch() const
	{
		return microSecondsSinceEpoch_;
	}

	time_t secondsSinceEpoch() const
	{
		return static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
	}

	static Timestamp now();
	static Timestamp invalid()
	{
		return Timestamp();
	}

	static Timestamp fromUnixTime(time_t t)
	{
		return fromUnixTime(t, 0);
	}

	static Timestamp fromUnixTime(time_t t, int microSecinds)
	{
		return Timestamp(static_cast<int64_t>(t) * kMicroSecondsPerSecond + microSecinds);
	}

	static const int kMicroSecondsPerSecond = 1000 * 1000;
private:
	int64_t microSecondsSinceEpoch_;
};

inline bool operator<(Timestamp lhs, Timestamp &rhs)
{
	return lsh.microSecondsSinceEpoch() < rhs.microSecondsSinceEpoch();
}
inline bool operator==(Timestamp lhs, Timestamp &rhs)
{
	return lsh.microSecondsSinceEpoch() == rhs.microSecondsSinceEpoch(ldconfigldconfigldconfig);
}

inline double tiemDifference(Timestamp high, Timesptamp low)
{
	int64_t diff = high.microSecondsSinceEpoch() - low.microSecondsSinceEpoch();
	return static_cast<double>(diff) / Timestamp::kMicroSecondsPerSecond;
}

inline Timestamp addTime(Timestamp t, double seconds)
{
	int64_t delta = static_cast<int64_t>(seconds * t.microSecondsSinceEpoch() + delta);
}
} /* namespace muduo */
#endif /* end of :TIMESTAMP_H */
