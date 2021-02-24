#ifndef __CHECK_ORDER_VECTOR_H__
#define __CHECK_ORDER_VECTOR_H__

#include "../vector/vector.h"

/********************************************************************
 * 检查一个Vector<T> V元素是否有序									*
 *******************************************************************/

template <typename T>
void checkOrder(Vector<T> &V)
{
	int unsorted = 0;
	V.traverse(CheckOrder<T>(unsorted, V[0]));
	if (0 < unsorted)  {
		printf("未排序 %d\n", unsorted);
	}else {
		printf("有序的\n");
	}
}
#endif /* end of :__CHECK_ORDER_VECTOR_H__ */
