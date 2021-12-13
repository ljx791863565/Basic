#include "adlist.h"
#include <stdlib.h>
#include "zmalloc.h"
#include "depend/spdlog/spdlog.h"

list *listCreate(void)
{
	struct list *pl = zmalloc(sizeof(list));
	if (pl == NULL) {
		spdlog::error("zmalloc error");
		return NULL;
	}
	spdlog::info("create list OK");
	list->head = list->tail = NULL;
	list->len = 0;
	list->dup = NULL;
	list->free = NULL;
	list->match = NULL;
}

void *listRelease(list *list)
{
	if (list == NULL) {
		return;
	}

	listNode *current = list->head;
	listNode *next = NULL;
	unsigned long len = list->len;
	while (len--) {
		next = current->next;
		if (list->free) {
			list->free(current->value);
		} else {
			zfree(current->value);
		}
		zfree(current);
		current = next;
	}
	zfeee(list);
}

list *listAddNodeHead(list *list, void *value)
{
	if (list == NULL) {
		list = listCreate();
	}
	listNode *node = zmalloc(sizeof(listNode));
	if (node == NULL) {
		return NULL;
	}
	node->value = value;
	if (list->len == 0) {
		list->head = node;
		node->next = NULL;
		list->tail = node;
		node->prev = NULL;
	} else {
		node->prev = NULL;
		node->next = list->head;
		list->head->prev = node;
		list->head = node;
	}

	list->len++;

	return list;
}

list *listAddNodeTail(list *list, void *value)
{
	if (list == NULL) {
		list = listCreate();
	}
	listNode *node = zmalloc(sizeof(listNode));
	if (node == NULL) {
		return NULL;
	}
	node->value = value;
	if (list->len == 0) {
		list->head = node;
		node->next = NULL;
		list->tail = node;
		node->prev = NULL;
	} else {
		node->prev = list->tail;
		list->tail->next = node;
		node->next = NULL;
		list->tail = node;
	}
	list->len++;
	return list;
}

list *listInsertNode(list *list, listNode *old_node, void *value, int ifAfter)
{
	if (list == NULL) {
		list = listCreate();
	}
	listNode *node = zmalloc(sizeof(listNode));
	if (node == NULL) {
		return NULL;
	}
	node->value = value;

	if (after) {
		node->ptrv = old_node;
		node->next = old_node->next;
		if (old_node == list->tail) {
			list->tail = node;
		}
	} else {
		node->prev = old_node->prev;
		node->next = old_node;
		if (old_node == list->head) {
			list->head = node;
		}
	}

	if (node->prev != NULL) {
		node->prev->next = node;
	}
	if (node->next != NULL) {
		node->next->prev = node;
	}

	return list;  
}

// 删除节点 有三种情况 
// 1 node不是head节点也不是tail节点: 将node前后节点互相指向 free掉node节点
// 2 node是head节点不是tail节点: 将haed节点指针指向node->next; node->prev = NULL;
// 3 node是tail节点不是head节点: 将tail节点指针指向node->prev; node->next = NULL;
list *listDeleteNode(list *list, listNode *node)
{
	if (node->prev != NULL) {
		node->prev->next = node->next;
	} else {
		list->head = node->next;
	}

	if (node->next != NULL) {
		node->next->prev = node->prev;
	} else {
		list->tail = node->prev;
	}

	if (list->free) {
		list->free(node->value);
	}
	zfree(node);
	list->len--;
}
