#ifndef ML_EVAL_H
#define ML_EVAL_H

#include "list.h"
#include "hashtable.h"
#include "parse.h"

hashtable_t *init_env();
tree_node_t *eval_ast(tree_node_t*, hashtable_t*);

#endif
