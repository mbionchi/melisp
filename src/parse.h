#ifndef ML_PARSE_H
#define ML_PARSE_H

#include "list.h"

enum ml_val_type {P_PROGRAM, P_SEXPR, P_LIST, P_SYMBOL, P_NUMBER, P_T, P_F};
typedef enum ml_val_type ml_val_type_t;

struct tree_node {
    ml_val_type_t type;
    void *val;
    node_t *children;
};
typedef struct tree_node tree_node_t;

tree_node_t *parse(node_t*);
void freetree(void*, void(*)(void*));

#endif
