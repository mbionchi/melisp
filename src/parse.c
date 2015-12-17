#include <stdlib.h>
#include <stdio.h>

#include "tokenize.h"
#include "vector.h"
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
    program->children = create_vector(4);
    push_back(program->children, parse_expr(&curr));
    return program;
}

void free_tree(void *tree) {
    if (!tree) {
        return;
    } else {
        if (((tree_node_t*)tree)->children) {
            free_vector(((tree_node_t*)tree)->children, free_tree);
        }
        if (((tree_node_t*)tree)->type == SYMBOL) {
            free(((tree_node_t*)tree)->val.sym);
        }
        free(tree);
    }
}

tree_node_t *parse_expr(node_t **curr) {
    tree_node_t *expr;
    if (((token_t*)(*curr)->val)->type == T_LPAREN) {
        *curr = (*curr)->next;
        expr = parse_list(curr);
    } else {
        expr = malloc(sizeof(tree_node_t));
        switch (((token_t*)(*curr)->val)->type) {
            case T_SYMBOL:
                expr->type = SYMBOL;
                break;
            case T_NUMBER:
                expr->type = NUMBER;
                break;
            case T_T:
                expr->type = T;
                break;
            case T_F:
                expr->type = F;
                break;
            default:
                printf("unexpected token\n");
                break;
        }
        expr->val = ((token_t*)(*curr)->val)->val;
        expr->children = NULL;
        *curr = (*curr)->next;
    }
    return expr;
}

tree_node_t *parse_list(node_t **curr) {
    tree_node_t *list = malloc(sizeof(tree_node_t));
    list->type = LIST;
    list->children = create_vector(8);
    while (((token_t*)(*curr)->val)->type != T_RPAREN) {
        push_back(list->children, parse_expr(curr));
    }
    *curr = (*curr)->next;
    return list;
}
