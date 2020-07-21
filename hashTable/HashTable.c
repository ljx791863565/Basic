#include "HashTable.h"

void initHashTable(Table *t)
{
	int i;
	if (t == NULL) {
		return;
	}
	for (i = 0; i < BUCKET_COUNT; i++) {
		t->bucket[i].key = NULL;
		t->bucket[i].value = NULL;
		t->bucket[i].next = NULL;
	}
}

void freeHashTable(Table *t)
{
	int i;
	Entry *e, *ep;
	if (t == NULL) {
		return;
	}
	for (i = 0; i < BUCKET_COUNT; i++) {
		e = &(t->bucket[i]);
		while (e->next != NULL) {
			ep = e->next;
			e->next = ep->next;
			free(ep->key);
			free(ep->value);
			free(ep);
		}
	}
}

int keyToIndex(const char *key)
{
	int i, index, len;
	if (key == NULL) {
		return -1;
	}
	len = strlen(key);
	index = (int)key[0];
	for (i = 0; i < len; i++) {
		index *= 1103515245 + (int)key[i];
	}
	index >>= 27;
	index &= (BUCKET_COUNT -1);

	return index;
}

int insertEntry(Table *t, const char *key, const char *value)
{
	int index, vlen1, vlen2;
	Entry *e, *ep;
	if (t == NULL || key == NULL || value == NULL) {
		return 0;
	}
	index = keyToIndex(key);
	if (t->bucket[index].key == NULL) {
		t->bucket[index].key = strdup(key);
		t->bucket[index].value = strdup(value);
	}else {
		e = &(t->bucket[index]);
		ep = e;
		while (e != NULL) {
			if (!strcmp(e->key, key)) {
				vlen1 = strlen(value);
				vlen2 = strlen(e->value);
				if (vlen1 > vlen2) {
					free(e->value);
					e->value = (char *)malloc(vlen1 +1);
				}
				memcpy(e->value, value, vlen1 +1);
				return index;
			}
			ep = e;
			e = e->next;
		}
		e = (Entry *)malloc(sizeof(Entry));
		if (e == NULL) {
			perror("malloc");
			return 0;
		}
		e->key = strdup(key);
		e->value = strdup(value);
		e->next = NULL;
		ep->next = e;
	}
	return index;
}

const char *findValueByKey(const Table *t, const char *key)
{
	int index;
	const Entry *e;
	if (t == NULL || key == NULL) {
		return NULL;
	}
	index = keyToIndex(key);
	e = &(t->bucket[index]);
	if (e->key == NULL) {
		return NULL;
	}
	while (e != NULL) {
		if (!strcmp(key, e->key)) {
			return e->value;
		}
		e = e->next;
	}
	return NULL;
}

Entry * removeEntry(Table *t, char *key)
{
	if (t == NULL || key == NULL) {
		return NULL;
	}
	int index = keyToIndex(key);
	Entry *e = &(t->bucket[index]);
	Entry *ep = NULL;
	while (e != NULL) {
		if (!strcmp(key, e->key)) {
			if (e == &(t->bucket[index])) {
				ep = e->next;
				if (ep != NULL) {
					Entry tmp = *ep;
					*e = *ep;
					*ep = tmp;
					ep->next = NULL;
				}else {
					ep = (Entry *)malloc(sizeof(Entry));
					if (ep == NULL) {
						perror("malloc");
						return NULL;
					}
					*ep = *e;
					e->key = e->value = NULL;
					e->next = NULL;
				}
			}else {
				ep = &(t->bucket[index]);
				while (ep->next != e) {
					ep = ep->next;
				}
				ep->next = e->next;
				e->next = NULL;
				ep = e;
			}
			return ep;
		}
		e = e->next;
	}
	return NULL;
}

void printTable(Table *t)
{
	int i;
	Entry *e = NULL;
	if (t == NULL) {
		return;
	}
	for (i = 0; i < BUCKET_COUNT; i++) {
		printf("bucket[%d]:\n", i);
		e = &(t->bucket[i]);
		while (e->key != NULL) {
			printf("\t%s : %s\n", e->key, e->value);
			if (e->next == NULL) {
				break;
			}
			e = e->next;
		}
	}
}
