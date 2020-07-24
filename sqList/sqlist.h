 // 线性表的动态分配顺序存储结构
#ifndef __SQ_LIST_H__
#define __SQ_LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include "basic.h"
#define LIST_INIT_SIZE 10 // 线性表存储空间的初始分配量
#define LISTINCREMENT 2 // 线性表存储空间的分配增量
struct SqList
{
	ElemType *elem; // 存储空间基址
	int length; // 当前长度
	int listsize; // 当前分配的存储容量(以sizeof(ElemType)为单位)
};

#endif
