#include "list.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>

List_t *List_init(void)
{
	List_t *list = (List_t *)malloc(sizeof(List_t));
	assert(list != NULL);
	list->next = NULL;
	return list;
}

List_t *List_push(List_t *list, void *val)
{
	List_t new_elem = (List_t *)malloc(sizeof(List_t));
	assert(new_elem != NULL);
	new_elem->val = val;
	new_elem->next = list;
	return new_elem;
}
int List_length(List_t *list);
void **List_to_Array(List_t *list);
List_t *List_append(List_t *list, List_t *tail);
List_t *List_traversal(List_t *list, void *val, ...);
List_t *List_copy(List_t *list);
List_t *List_pop(List_t *list);
