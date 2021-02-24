#ifndef __DOUBLE_ELEM_H__
#define __DOUBLE_ELEM_H__

/******************************************************************
 *	倍增一个T类型对象
 ******************************************************************/

template <typename T>
class Double
{
public:
	virtual void operator()(T &e)
	{
		e *= 2;
	}
};
#endif /* end of :__DOUBLE_ELEM_H__ */
