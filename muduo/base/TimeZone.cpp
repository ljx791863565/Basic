#include "TimeZone.h"
#include "Nomcopyable.h"
#include "Date.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include <assert.h>
#include <endian.h>
#include <stdio.h>

namespace muduo {
namespace detail {

struct Transition
{
	time_t gmttime;
	time_t localtime;
	int localtimeIdx;

	Transition(time_t gt, time_t lot, int localIdx)
		:gmttime(gt), localtime(lot), localtimeIdx(localIdx)
	{}
};

struct Comp
{
	bool compareGmt;
	Comp(bool gmt)
		: compareGmt(gmt)
	{}

	bool operator()(const Transition& lhs, const Transition& rhs) const
	{
		if (compareGmt)  {
			return lhs.gmttime < rhs.gmttime;
		}else {
			return lhs.localtime < rhs.localtime;
		}
	}

	bool equal(const Transition& lhs, const Transition& rhs) const
	{
		if (compareGmt)  {
			return lhs.gmttime < rhs.gmttime;
		}else {
			return lhs.localtime < rhs.localtime;
		}
	}
};

struct Localtime
{
	time_t gmtOffset;
	bool isDst;
	int arrbIdx;

	Localtime(time_t offset, bool dst, int arrb)
		: gmtOffset(offset), isDst(dst), arrbIdx(arrb)
	{}
};

inline void fillHMS(unsigned seconds, struct tm* utc)
{
	utc->tm_sec = seconds % 60;
	unsigned minutes = seconds / 60;
	utc->tm_min = minutes % 60;
	utc->tm_hour = minutes / 60;
}
} /* namespace detail */
const int kSecondsPerDay = 24*60*60;
} /* namespace muduo */

using namespace muduo;
using namespace std;
struct TimeZone::Data
{
	vector<detail::Transition> transition;
	vector<datail::Localtime> localtime;
	vector<string> names;
	string abbreviation;
};

namespace muduo {
namespace detail {
class File : Noncopyable
{
public:
	File(const char *file)
		:fp_(::fopen(file, "rb"))
	{}
	~File()
	{
		if (fp_)  {
			::fclose(fp_);
		}
	}

	bool valid() const
	{
		return fp_;
	}

	string readBytes(int n)
	{
		char buf[n] = {0};
		ssize_t nr = ::fread(buf, 1, n, fp_);
		if (nr != n)  {
			throw logic_error("no enough data");
		}
		return string(buf, n);
	}

	int32_t readInt32()
	{
		int32_t x = 0;
		ssize_t nr = ::fread(&x, 1, sizeof(x), fp_);
		if (nr != sizeof(x))  {
			throw logic_error("bad int32_t data");
		}
		//big endian to host
		return be32toh(x);	
	}

	uint8_t readUInt8()
	{
		uint8_t x = 0;
		ssize_t nr = ::fread(&x, 1, sizeof(x), fp_);
		if (nr != sizeof(x))  {
			throw logic_error("bad uint8_t data");
		}
		return x;
	}
	
private:
	FILE *fp_;
};

bool readTimeZoneFile(const char *zonefile, struct timeZone::Date *date)
{
	File f(zonefile);
	if (f.valid())  {
		try {
			string head  = f.readBytes(4);
			if (head != "TZif")  {
				throw logic_error("bad head");
			}
			string version = f.readBytes(1);
			f.readBytes(15);

			int32_t isgmtcnt = f.readInt32();
			int32_t isstdcnt = f.readInt32();
			int32_t leapcnt = f.readInt32();
			int32_t timecnt = f.readInt32();
			int32_t typecnt = f.readInt32();
			int32_t charcnt = f.readInt32();

			vector<int32_t> trans;
			vector<int> localtime;
			trans.reserve(timecnt);
			for (int i = 0; i < timecnt; i++) {
				trans.push_back(f.readInt32());
			}
			for (int i = 0; i < timecnt; i++) {
				uint8_t local = f.readUInt8();
				localtime.push_back(local);
			}
			for (int i = 0; i < typecnt; i++) {
				int32_t gmtoff = f.readInt32();
				uint8_t isdst = f.readUInt8();
				uint8_t abbrind = f.readUInt8();

				data->localtimes.push_back(Localtime(gmtoff, isdst, abbrind));
			}
			for (int i = 0; i < timecnt; i++) {
				int localIdx = localtimes[i];
				time_t localtime = trams[i] + data->localtimes[localIdx].gmtOffset;
				data->transition.push_back(Transition(trans[i], localtime, localIdx));
			}

			data->abbreviation = f.readBytes(charcnt);

			for (int i = 0; i < leapcnt; i++) {
			
			}
		}
		catch (logic_error &e) {
			fprintf(stderr, "%s\n", e.what());
		}
	}	
	return true;
}
} /* namespace detail */
} /* namespace muduo */

TimeZone::TimeZone(const char *zonefile)
	:data_(new TimeZone::Data)
{
	if (!detail::readTimeZoneFile(zonefile, data_.get()))  {
		data_.reset();
	}
}

TimeZone::TimeZone(int eastOfUtc, const char *name)
	:data_(new TimrZone::Data)
{
	data_->localtimes.push_back(detail::Localtime(eastOfUtc, false, 0));
	data_->abbreviation = name;
}

struct timeZone::toLocaltime(time_t seconds) const
{
	struct tm loaclTime;
	memZero(&localTime, sizeof(localTime));
	assert(data_ != NULL);
	const Data& data(*data_);
}
