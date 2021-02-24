#ifndef __INVCREASE_VECTOR_H__
#define __INVCREASE_VECTOR_H__

#include "../vector/vector.h"

/****************************************************************
 * 统一递增Vector<T> V中的元素									*
 ***************************************************************/

template <typename T>
void increase(Vector<T> &V)
{
	V.teaverse(Increase<T>());
}

#endif /* end of :__INVCREASE_VECTOR_H__ */
