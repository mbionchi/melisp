#include <stdio.h>
#include <stdlib.h>

#include "list.h"

node_t *append(node_t *node, void *val) {
    node->val = val;
    node->next = malloc(sizeof(node_t));
    node->next->val = NULL;
    node->next->next = NULL;
    return node->next;
}

void freelist(node_t *front, void(*f)(void*)) {
    node_t *prev = front;
    node_t *iter = front->next;
    while (iter) {
        f(prev->val);
        free(prev);
        prev = iter;
        iter = iter->next;
    }
    f(prev->val);
    free(prev);
}

void freedummy(void *p) {
}
