#ifndef ML_PARSE_H
#define ML_PARSE_H

#include "list.h"
#include "vector.h"
#include "tokenize.h"

enum ml_val_type {PROGRAM, SEXPR, QEXPR, LIST, SYMBOL, NUMBER, T, F};
typedef enum ml_val_type ml_val_type_t;

struct tree_node {
    ml_val_type_t type;
    ml_val_t val;
    vector_t *children;
};
typedef struct tree_node tree_node_t;

tree_node_t *parse(node_t*);
void free_tree(tree_node_t*);

#endif
