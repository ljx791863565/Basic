#ifndef __CHECK_ORDER_ELEM_H__
#define __CHECK_ORDER_ELEM_H__

/****************************************************************
 * 判断一个T类型对象是否局部有序								*	
 * *************************************************************/

template <typename T>
class CheckOrder
{
public:
	T pred;
	int &u;
	CheckOrder(int &unsorted, T &first)
		:pred(first), u(unsorted)
	{}

	virtual void operator()(T &e)
	{
		if (pred > e)  {
			u++;
			pred = e;
		}
	}
};
#endif /* end of :__CHECK_ORDER_ELEM_H__ */
