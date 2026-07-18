#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>
#include <stdlib.h>

struct Node {
	char *key;
	int value;
	struct Node *next;
};

struct HTable {
	struct Node **buckets;
	size_t size;
};

struct HTable *create_table(size_t size);
bool insert(struct HTable *table, const char *key, int value);
bool search(struct HTable *table, const char *key, int *result);
void noderemove(struct HTable *table, const char *key);
void freetable(struct HTable *table);

#endif
