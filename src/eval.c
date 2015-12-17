#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "eval.h"

#include "list.h"
#include "parse.h"

/*
tree_node_t *add_func(tree_node_t *itself, node_t *args) {
    if (!args) {
        return itself;
    } else {
        tree_node_t *tn = malloc(sizeof(tree_node_t));
        tn->children = NULL;
        tn->val.num = 0;
        tn->type = NUMBER;
        while (args) {
            if (!args->val || ((tree_node_t*)args->val)->type != NUMBER) {
                free(tn);
                printf("error: +: expected a number\n");
                return NULL;
            }
            tn->val.num += ((tree_node_t*)args->val)->val.num;
            args = args->next;
        }
        return tn;
    }
}

hashmap_t *init_env() {
    env_t *env = malloc(sizeof(env_t));
    env->pairs = malloc(sizeof(node_t));
    node_t *iter = env->pairs, *prev = NULL;
    pair_t *add_builtin = malloc(sizeof(pair_t));
    add_builtin->sym = malloc(sizeof(char)*2);
    strcpy(add_builtin->sym, "+");
    add_builtin->f = add_func;
    prev = append(&iter, add_builtin);
    prev->next = NULL;
    free(iter);
    return env;
}

tree_node_t *lookup(tree_node_t *itself, char *sym, node_t* args, env_t *env) {
    node_t *iter = env->pairs;
    while (iter) {
        if (!strcmp(((pair_t*)iter->val)->sym, sym)) {
            return ((pair_t*)iter->val)->f(itself, args);
        }
        iter = iter->next;
    }
    return NULL;
}

tree_node_t *eval_ast(tree_node_t *tree, env_t *env) {
    tree_node_t *rv, *lv;
    switch (tree->type) {
        case NUMBER:
        case T:
        case F:
            rv = tree;
            break;
        case SYMBOL:
            lv = lookup(tree, tree->val.sym, NULL, env);
            if (!lv) {
                printf("error: unknown symbol %s\n", tree->val.sym);
                rv = NULL;
            } else if (lv == tree) {
                rv = tree;
            } else {
                free(tree->val.sym);
                free(tree);
                rv = lv;
            }
            break;
        case LIST:
            rv = tree;
            break;
        case PROGRAM:
            break;
    }
    return rv;
}
*/
