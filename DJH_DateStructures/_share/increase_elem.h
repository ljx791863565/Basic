#ifndef __INCREASE_ELEM_H__
#define __INCREASE_ELEM_H__

template <typename T>
class Increase
{
public:
	virtual void operator()(T &e)
	{
		e++;
	}
};
#endif /* end of :__INCREASE_ELEM_H__ */
