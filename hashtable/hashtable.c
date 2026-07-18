#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

static unsigned int hash_djb2(const char *str) {
	if (str == NULL)
		return 0;

	const unsigned char *key = (const unsigned char *)str;

	unsigned int hash = 5381;

	for (unsigned int c = 0; (c = *key++);) {
		hash = ((hash << 5) + hash) + c;
	}
	return hash;
}

static unsigned int gethashindex(unsigned int hash, size_t size) {
	return hash % size;
}

struct HTable *create_table(size_t size) {
	if (size == 0)
		return NULL;
	struct HTable *table = (struct HTable *)malloc(sizeof(struct HTable));

	if (!table)
		return NULL;

	table->buckets = (struct Node **)malloc(sizeof(struct Node *) * size);

	if (!table->buckets) {
		free(table);
		return NULL;
	}

	for (size_t i = 0; i < size; i++) {
		table->buckets[i] = NULL;
	}
	table->size = size;
	return table;
}

static struct Node *search_node(struct HTable *table, const char *key) {
	if (!table || !key || key[0] == '\0')
		return NULL;

	unsigned int index = gethashindex(hash_djb2(key), table->size);
	struct Node *item = table->buckets[index];

	while (item) {
		if (strcmp(item->key, key) == 0) {
			return item;
		}
		item = item->next;
	}

	return NULL;
}

bool search(struct HTable *table, const char *key, int *result) {
	struct Node *ptrnode = search_node(table, key);
	if (ptrnode) {
		*result = ptrnode->value;
		return true;
	}
	return false;
}

bool insert(struct HTable *table, const char *key, int value) {

	if (!table || !key || key[0] == '\0')
		return false;

	struct Node *pnode = search_node(table, key);
	if (pnode) {
		pnode->value = value;
		return true;
	}

	unsigned int index = gethashindex(hash_djb2(key), table->size);

	struct Node *tmp = (struct Node *)malloc(sizeof(struct Node));
	if (!tmp) {
		return false;
	}

	tmp->key = (char *)malloc(strlen(key) + 1);
	if (!tmp->key) {
		free(tmp);
		return false;
	}

	strcpy(tmp->key, key);
	tmp->value = value;

	tmp->next = table->buckets[index];

	table->buckets[index] = tmp;

	return true;
}

void noderemove(struct HTable *table, const char *key) {
	if (!table || !key || key[0] == '\0')
		return;

	unsigned int index = gethashindex(hash_djb2(key), table->size);

	struct Node *current = table->buckets[index];
	struct Node *previous = NULL;

	while (current) {
		if (strcmp(current->key, key) == 0)
			break;
		previous = current;
		current = current->next;
	}

	if (!current) {
		return;
	}
	if (previous) {
		previous->next = current->next;
	} else {
		table->buckets[index] = current->next;
	}

	free(current->key);
	free(current);
	return;
}

void freetable(struct HTable *table) {
	if (!table) {
		return;
	}

	for (size_t i = 0; i < table->size; i++) {
		struct Node *current = table->buckets[i];
		while (current) {
			struct Node *tmp = current;
			current = current->next;

			free(tmp->key);
			free(tmp);
		}
	}

	free(table->buckets);
	free(table);
}
