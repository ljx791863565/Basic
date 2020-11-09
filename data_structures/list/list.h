#ifndef __LIST_H__
#define __LIST_H__

typedef struct List
{
	void *val;
	struct List *next; 
}List_t;

List_t *List_init(void);
List_t *List_push(List_t *list, void *val);
int List_length(List_t *list);
void **List_to_Array(List_t *list);
List_t *List_append(List_t *list, List_t *tail);
List_t *List_traversal(List_t *list, void *val, ...);
List_t *List_copy(List_t *list);
List_t *List_pop(List_t *list);

#endif
