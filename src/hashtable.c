#include "hashtable.h"

#include <string.h>
#include "list.h"

hashtable_t *create_hashtable(ssize_t size) {
    hashtable_t *table = malloc(sizeof(hashtable_t));
    int i;
    table->psize = size;
    table->pairs = malloc(sizeof(node_t*)*size);
    for (i=0; i<size; i++) {
        table->pairs[i] = NULL;
    }
    return table;
}

void put(hashtable_t *table, char *key, void *val) {
    /* placeholder */
}

void *get(char *key) {
    /* placeholder */
}

/* a highly naive hash function */
unsigned int hash(char *s) {
    unsigned int result = 0x00;
    char *iter;
    int i;
    for (i=0; i<8; i++) {
        iter = s;
        while (*iter) {
            result ^= (*iter & 0xFF) << (i*3);
            iter++;
        }
    }
    return result;
}
