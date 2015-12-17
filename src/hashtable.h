#ifndef ML_HASHMAP_H
#define ML_HASHMAP_H

#include <stdlib.h>

#include "list.h"

struct pair {
    char *key;
    void *val;
};
typedef struct pair pair_t;

struct hashtable {
    node_t **pairs;
    size_t psize;
};
typedef struct hashtable hashtable_t;

void add(hashtable_t*, char*, void*);
unsigned int hash(char*);

#endif
