#ifndef ML_EVAL_H
#define ML_EVAL_H

#include "list.h"
#include "parse.h"

struct env {
    node_t *pairs;
};
typedef struct env env_t;

struct pair {
    char *sym;
    tree_node_t*(*f)(tree_node_t*,node_t*);
};
typedef struct pair pair_t;

env_t *init_env();
tree_node_t *eval_ast(tree_node_t*, env_t*);

#endif
