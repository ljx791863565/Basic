// sLinkList.h 线性表的静态单链表存储结构
#include "../basic.h"
#define MAXSIZE 100 // 链表的最大长度
typedef struct
{
	ElemType data;
	int cur;
}component,SLinkList[MAXSIZE];
