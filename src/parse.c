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
    program->children = create_vector(8);
    push_back(program->children, parse_expr(&curr));
    return program;
}

void free_tree(tree_node_t *tree) {
    /*
    if (!tree) {
        return;
    } else {
        node_t *iter = tree->children;
        node_t *prev;
        while (iter) {
            prev = iter;
            iter = iter->next;
            free_tree((tree_node_t*)prev->val);
            free(prev);
        }
        if (tree->type == SYMBOL) {
            free(tree->val.sym);
        }
        free(tree);
    }
    */
}

tree_node_t *parse_expr(node_t **curr) {
    tree_node_t *expr = malloc(sizeof(tree_node_t));
    if (((token_t*)(*curr)->val)->type == T_QUOTE) {
        expr->type = QEXPR;
        *curr = (*curr)->next;
    } else {
        expr->type = SEXPR;
    }
    expr->children = create_vector(1);
    if (((token_t*)(*curr)->val)->type == T_LPAREN) {
        push_back(expr->children, parse_list(curr));
    } else {
        tree_node_t *leaf = malloc(sizeof(tree_node_t));
        switch (((token_t*)(*curr)->val)->type) {
            case T_SYMBOL:
                leaf->type = SYMBOL;
                break;
            case T_NUMBER:
                leaf->type = NUMBER;
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
        leaf->val = ((token_t*)(*curr)->val)->val;
        leaf->children = create_vector(0);
        push_back(expr->children, leaf);
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
