#ifndef __TIMER_H__
#define __TIMER_H__
#include <iostream>
#include <chrono>

using namespace std::chrono;
class Timer{
public:
	Timer ()
		:m_begin(high_resolution_clock::now())
	{}

	void reset()
	{
		m_begin = high_resolution_clock::now();
	}

	template <typename Duration=milliseconds>
	int64_t elapsed() const 
	{
		return duration_cast<Duration>(high_resolution_clock::now() - m_begin).count();
	}

	int64_t elapsed_micro() const 
	{
		return elapsed<milliseconds>();
	}

	int64_t elapsed_nano() const 
	{
		return elapsed<nanoseconds>();
	}
	
	int64_t elapsed_seconds() const 
	{
		return elapsed<seconds>();
	}

	int64_t elapsed_minutes() const 
	{
		return elapsed<minutes>();
	}

	int64_t elapsed_hours() const 
	{
		return elapsed<hours>();
	}
private:
	time_point<high_resolution_clock> m_begin;
	/* data */
};
#endif /* end of :__TIMER_H__ */



