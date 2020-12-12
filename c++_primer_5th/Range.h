#ifndef __RANGE_H__
#define __RANGE_H__

#include <iostream>
#include <stdexcept>
template <typename T>
class RangeImpl
{
	class Iterator;
public:
	RangeImpl(T begin, T end, T step = 1) :m_begin(begin), m_end(end), m_step(step)
	{
		if (step > 0 && m_begin >= m_end)  {
			throw std::logic_error("end must greater then begin");
		}else if (step < 0 && m_end >= m_begin) {
			throw std::logic_error("begin must greater then end");
		}
		m_step_end = (m_end - m_begin) / m_step;
		if (m_begin + m_step * m_step_end != m_end)  {
			++m_step_end;
		}
	}

	Iterator begin()
	{
		return Iterator(0, *this);
	}
 
	Iterator end()
	{
		return Iterator(m_step_end, *this);
	}

	T operator[](int s)
	{
		return m_begin + s*m_step;
	}

	int size()
	{
		return m_step_end;
	}
private:
	T m_begin;
	T m_end;
	T m_step;
	int m_step_end;

	class Iterator
	{
	public:
		Iterator(int start, RangeImpl& range): m_current_step(start), m_range(range)
		{
			m_current_value = m_range.m_begin + m_current_step * m_range.m_step;
		}

		T operator*()
		{
			return m_current_value;
		}

		const Iterator* operator++()
		{
			m_current_value += m_range.m_step;
			m_current_step++;
			return this;
		}

		bool operator==(const Iterator &other)
		{
			return m_current_step == other.m_current_step;
		}

		bool operator!=(const Iterator &other)
		{
			return m_current_step != other.m_current_step;
		}

		const Iterator* operator--()
		{
			m_current_value += m_range.m_step;
			m_current_step --;
			return this;
		}
	private:
		T m_current_value;
		int m_current_step;
		RangeImpl& m_range;
	};
};

template <typename T, typename U>
auto Range(T begin, T end, U stepsize) ->RangeImpl<decltype(begin + stepsize)>
{
	return RangeImpl<decltype(begin + stepsize)>(begin, end, stepsize);
}

template <typename T>
RangeImpl<T> Range(T begin, T end)
{
	return RangeImpl<T>(begin, end, 1);
}

template <typename T>
RangeImpl<T> Range(T end)
{
	return RangeImpl<T>(T(), end, 1);
}
#endif /* end of :__RANGE_H__ */
