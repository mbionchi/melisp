#include <stdlib.h>
#include <stdio.h>

#include "tokenize.h"
#include "list.h"
#include "parse.h"

tree_node_t *parse_program(node_t*);
tree_node_t *parse_expr(node_t**);
tree_node_t *parse_list(node_t**);

tree_node_t *parse(node_t *tokens) {
    tree_node_t *program = parse_program(tokens);
    return program;
}

tree_node_t *parse_program(node_t *curr) {
    tree_node_t *program = malloc(sizeof(tree_node_t));
    program->type = PROGRAM;
    program->children = malloc(sizeof(node_t));
    node_t *iter = program->children;
    node_t *prev = NULL;
    while (curr) {
        prev = append(&iter, parse_expr(&curr));
    }
    prev->next=NULL;
    free(iter);
    return program;
}

/*
void freetree(void *tree, void(*f)(void*)) {
    if (!tree) {
        return;
    } else {
        node_t *iter = ((tree_node_t*)tree)->children;
        node_t *prev;
        while (iter) {
            prev = iter;
            iter = iter->next;
            freetree(prev->val, f);
            free(prev);
        }
        f(((tree_node_t*)tree)->val);
        free(tree);
    }
}*/

tree_node_t *parse_expr(node_t **curr) {
    tree_node_t *expr = malloc(sizeof(tree_node_t));
    if (((token_t*)(*curr)->val)->type == T_QUOTE) {
        expr->type = QEXPR;
        *curr = (*curr)->next;
    } else {
        expr->type = SEXPR;
    }
    expr->children = malloc(sizeof(node_t));
    node_t *iter = expr->children;
    node_t *prev = NULL;
    if (((token_t*)(*curr)->val)->type == T_LPAREN) {
        *curr = (*curr)->next;
        prev = append(&iter, parse_list(curr));
        prev->next = NULL;
        free(iter);
    } else {
        tree_node_t *leaf = malloc(sizeof(tree_node_t));
        switch (((token_t*)(*curr)->val)->type) {
            case T_SYMBOL:
                leaf->type = SYMBOL;
                leaf->val.sym = ((token_t*)(*curr)->val)->val.sym;
                break;
            case T_NUMBER:
                leaf->type = NUMBER;
                leaf->val.num = ((token_t*)(*curr)->val)->val.num;
                break;
            case T_T:
                leaf->type = T;
                break;
            case T_F:
                leaf->type = F;
                break;
            default:
                printf("unexpected token\n");
                break;
        }
        //leaf->val = ((token_t*)(*curr)->val)->val;
        leaf->children = NULL;
        iter->val = leaf;
        iter->next = NULL;
        *curr = (*curr)->next;
    }
    return expr;
}

tree_node_t *parse_list(node_t **curr) {
    tree_node_t *list = malloc(sizeof(tree_node_t));
    list->type = LIST;
    list->children = malloc(sizeof(node_t));
    node_t *iter = list->children;
    node_t *prev = NULL;
    while (((token_t*)(*curr)->val)->type != T_RPAREN) {
        prev = append(&iter, parse_expr(curr));
    }
    *curr = (*curr)->next;
    prev->next = NULL;
    free(iter);
    return list;
}
