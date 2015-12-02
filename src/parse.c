#include <stdlib.h>

#include "tokenize.h"
#include "parse.h"

tree_node_t *parse_program(node_t*);
tree_node_t *parse_sexpr(node_t**);
tree_node_t *parse_list(node_t**);

tree_node_t *parse(node_t *tokens) {
    tree_node_t *program = parse_program(tokens);
    return program;
}

tree_node_t *parse_program(node_t *curr) {
    tree_node_t *program = malloc(sizeof(tree_node_t));
    program->type = P_PROGRAM;
    program->val = NULL;
    program->children = malloc(sizeof(node_t));
    node_t *iter = program->children;
    node_t *prev = NULL;
    while (curr) {
        prev = append(&iter, parse_sexpr(&curr));
    }
    prev->next=NULL;
    free(iter);
    return program;
}

tree_node_t *parse_sexpr(node_t **curr) {
    tree_node_t *sexpr = malloc(sizeof(tree_node_t));
    sexpr->type = P_SEXPR;
    sexpr->val = NULL;
    sexpr->children = malloc(sizeof(node_t));
    node_t *iter = sexpr->children;
    node_t *prev = NULL;
    if (((token_t*)((*curr))->val)->type == LPAREN) {
        *curr = (*curr)->next;
        prev = append(&iter, parse_list(curr));
        prev->next = NULL;
        free(iter);
    } else {
        tree_node_t *leaf = malloc(sizeof(tree_node_t));
        switch (((token_t*)(*curr)->val)->type) {
            case SYMBOL:
                leaf->type = P_SYMBOL;
                break;
            case NUMBER:
                leaf->type = P_NUMBER;
                break;
            case T:
                leaf->type = P_T;
                break;
            case F:
                leaf->type = P_F;
                break;
            default:
                break;
        }
        leaf->val = ((token_t*)(*curr)->val)->value;
        leaf->children = NULL;
        iter->val = leaf;
        iter->next = NULL;
        *curr = (*curr)->next;
    }
    return sexpr;
}

tree_node_t *parse_list(node_t **curr) {
    tree_node_t *list = malloc(sizeof(tree_node_t));
    list->type = P_LIST;
    list->val = NULL;
    list->children = malloc(sizeof(node_t));
    node_t *iter = list->children;
    node_t *prev = NULL;
    while (((token_t*)(*curr)->val)->type != RPAREN) {
        prev = append(&iter, parse_sexpr(curr));
    }
    *curr = (*curr)->next;
    prev->next = NULL;
    free(iter);
    return list;
}
