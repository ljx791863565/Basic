#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_COUNT 16		//哈希表中节点数组大小

typedef struct HashEntry {
	char *key;
	char *value;
	struct HashEntry *next;
} Entry;

typedef struct HashTable {
	Entry bucket[BUCKET_COUNT];
} Table;

void initHashTable(Table *t);
void freeHashTable(Table *t);
int keyToIndex(const char *key);
int insertEntry(Table *t, const char *key, const char *value);
const char *findValueByKey(const Table *t, const char *key);
Entry *removeEntry(Table *t, char *key);
void printTable(Table *t);

#endif
