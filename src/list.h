#ifndef ML_LIST_H
#define ML_LIST_H

struct node {
    void *val;
    struct node *next;
};
typedef struct node node_t;

node_t *append(node_t**, void*);
void freelist(node_t*, void(*)(void*));
void freelist2(node_t*, void(*)(void*, void(*)(void*)), void(*)(void*));
void freedummy(void*);

#endif
