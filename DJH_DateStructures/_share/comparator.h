#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__


/********************************************************************
 * 比较函数lt eq													*
 *******************************************************************/

template <typename T>
static bool lt(T* a, T* b)
{
	return lt(*a, *b);
}

template <typename T>
static bool lt(T &a, T &b)
{
	return a<b;
}

template <typename T>
static bool eq(T* a, T* b)
{
	return eq(*a, *b);
}

template <typename T>
static bool eq(T &a, T &b)
{
	return a==b;
}
#endif /* end of :__COMPARATOR_H__ */
