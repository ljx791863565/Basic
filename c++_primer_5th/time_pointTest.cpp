#include <iostream>
#include <iomanip>
#include <ratio>
#include <chrono>
#include <ctime>	//std::put_time
int main(int argc, const char *argv[])
{
	using namespace std::chrono;

	typedef duration<int, std::ratio<60*60*24>> days_type;
	typedef duration<int, std::ratio<60*60*24*365>> years_type;
	time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
	time_point<system_clock, years_type> thisyear = time_point_cast<years_type>(system_clock::now());

	//输出从1970.1.1到现在的天和年
	std::cout << today.time_since_epoch().count() << "days since epoch" << std::endl;
	std::cout << thisyear.time_since_epoch().count() << "years since epoch" << std::endl;

	system_clock::time_point now = system_clock::now();
	std::time_t nowtime = system_clock::to_time_t(now);
	std::time_t last = system_clock::to_time_t(now - hours(24));
	std::time_t next = system_clock::to_time_t(now + hours(24));

	//输出24小时前的时间和24小时后的时间
	//%F YYYY-MM-DD日期的简写，	相当于％Y-％m-％d
	//%T SO 8601时间格式 (HH:MM:SS)，相当于%H:%M:%S
	std::cout << "now the time is " << std::put_time(std::localtime(&nowtime), "%F %T") << '\n';
	std::cout << "One day ago, the time was " << std::put_time(std::localtime(&last), "%F %T") << '\n';
	std::cout << "Next day, the time is " << std::put_time(std::localtime(&next), "%F %T") << '\n';

	system_clock::time_point t1 = system_clock::now();
	std::cout << "Hello World..." << std::endl;
	system_clock::time_point t2 = system_clock::now();

	std::cout << (t2 - t1).count() << " tick count" << std::endl;
	std::cout << duration_cast<nanoseconds>(t2-t1).count() << " nanoseconds" << std::endl;
	return 0;
}
