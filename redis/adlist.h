#ifndef _ADLIST_H_
#define _ADLIST_H_ 

/*
 *			listNode 
 *			+--------+		+--------+
 *	NULL<--	|  prev	 | <--- | prev	 |		
 *			|--------|		|--------+
 *			|  next	 | ---> | next	 | ----> NULL 
 *			+--------+		+--------+
 *			|  value |		|  value |
 *			+--------+		+--------+
 */ 
typedef struct listNode {
	struct listNode *next;
	struct listNode *ptrv;
	void *value;	// void* 类型表示该链表支持任意格式数据
}listNode;

typedef void *(*fun_dup)(void *);
typedef void (fun_free)(void *);
typedef void (fun_match)(void *, void *);
typedef struct list {
	listNode *head;
	listNode *tail;
	unsigned long len;
	fun_dup dup;
	fun_free free;
	fun_match match;
}list;

typedef struct listIter {
	listNode *next;
	int drection;
} listIter;

static inline unsigned long listLength(list *list)
{
	return list->len;
}

static inline listNode *listFirst(list *list)
{
	return list->head;
}

static inline listNode *listLast(list *list)
{
	return list->tail;
}


static inline void listSetDupMethod(list *list, fun_dup Dup)
{
	list->dup = Dup;
}

static inline fun_dup listGetDupMethod(list *list)
{
	return list->dup;
}

static inline void listSetFreeMethod(list *list, fun_free Free)
{
	list->free = Free;
}

static inline fun_free listGetFreeMethod(list *list)
{
	return list->free;
}

static inline void listSetMatchMethod(list *list, fun_match Match)
{
	list->match = Match;
}

static inline fun_match listGetMatchMethod(list *list)
{
	return list->match;
}
// 创建双链表
list *listCreate(void);
// 销毁双链表
void *listRelease(list *list);
// 在双链表头部插入一个节点
list *listAddNodeHead(list *list, void *value);
// 在双链表尾部插入一个节点
list *listAddNodeTail(list *list, void *value);
// 在双链表old_node节点前/后插入一个节点 
list *listInsertNode(list *list, listNode *old_node, void *value, int isAfter);
list *listDeleteNode(list *list, listNode *node);

listIter *listGetIterator(list *list, q)
#endif /* end _ADLIST_H_ */
