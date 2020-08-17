// c2-2.h 线性表的单链表存储结构
#ifndef __LINK_LIST_H__
#define __LINK_LIST_H__
struct LNode
{
	ElemType data;
	LNode *next;
};
typedef LNode *LinkList; // 另一种定义LinkList的方法

#endif //__LINK_LIST_H__
