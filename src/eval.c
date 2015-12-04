#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "eval.h"

#include "list.h"
#include "parse.h"

void eval_ast(tree_node_t **tree, env_t *env) {
    if (*tree) {
        tree_node_t *tmp;
        node_t *first, *iter, *next, *prev;
        char *sym;
        switch ((*tree)->type) {
            case P_NUMBER:
                break;
            case P_SYMBOL:
                break;
            case P_LIST:
                iter = (*tree)->children;
                while (iter) {
                    eval_ast((tree_node_t**)&iter->val, env);
                    iter = iter->next;
                }
                first = (*tree)->children;
                if (first) {
                    if (((tree_node_t*)first->val)->type == P_SYMBOL) {
                        sym = ((tree_node_t*)first->val)->val;
                        if (!strcmp(sym,"+")) {
                            iter = first->next;
                            if (iter && ((tree_node_t*)iter->val)->type == P_NUMBER) {
                                next = iter->next;
                                while (next) {
                                    prev = next;
                                    tmp = (tree_node_t*)next->val;
                                    if (tmp->type == P_NUMBER) {
                                        *(int*)((tree_node_t*)iter->val)->val += *(int*)tmp->val;
                                    } else {
                                        printf("error: + expects a number\n");
                                        break;
                                    }
                                    next = next->next;
                                    free(tmp->val);
                                    free(tmp);
                                    free(prev);
                                }
                                iter->next = NULL;
                                free(*tree);
                                *tree = (tree_node_t*)iter->val;
                                free(first);
                            }
                        }
                    }
                }
                break;
            case P_SEXPR:
                tmp = *tree;
                *tree = (tree_node_t*)(*tree)->children->val;
                free(tmp);
                eval_ast(tree, env);
                break;
            case P_T:
                break;
            case P_F:
                break;
            case P_PROGRAM:
                iter = (*tree)->children;
                while (iter) {
                    eval_ast((tree_node_t**)&iter->val, env);
                    iter = iter->next;
                }
                break;
        }
    }
}
