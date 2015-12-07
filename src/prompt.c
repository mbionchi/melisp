#include <stdio.h>
#include <stdlib.h>

#include "tokenize.h"
#include "list.h"
#include "parse.h"
#include "eval.h"

char *getindent(int n) {
    char *str = malloc(sizeof(char)*n+1);
    int i;
    for (i=0; i<n; i++) {
        str[i] = ' ';
    }
    str[n] = '\0';
    return str;
}

void print_tokens(node_t *iter) {
    while (iter) {
        token_t *token = iter->val;
        switch (token->type) {
            case T_LPAREN:
                printf("LEXER: LPAREN\n");
                break;
            case T_RPAREN:
                printf("LEXER: RPAREN\n");
                break;
            case T_SYMBOL:
                printf("LEXER: SYMBOL %s\n", token->val.sym);
                break;
            case T_NUMBER:
                printf("LEXER: NUMBER %ld\n", token->val.num);
                break;
            case T_T:
                printf("LEXER: TRUE\n");
                break;
            case T_F:
                printf("LEXER: FALSE\n");
                break;
            case T_QUOTE:
                printf("LEXER: QUOTE\n");
                break;
            default:
                printf("WTF???\n");
                break;
        }
        iter = iter->next;
    }
}

void print_ast_full(tree_node_t *tree, int indent) {
    if (!tree) {
        return;
    } else {
        switch (tree->type) {
            case PROGRAM:
                fprintf(stderr,"%sPROGRAM\n", getindent(indent));
                break;
            case QEXPR:
                fprintf(stderr,"%sQEXPR\n", getindent(indent));
                break;
            case SEXPR:
                fprintf(stderr,"%sSEXPR\n", getindent(indent));
                break;
            case LIST:
                fprintf(stderr,"%sLIST\n", getindent(indent));
                break;
            case SYMBOL:
                fprintf(stderr,"%sSYMBOL: %s\n", getindent(indent), tree->val.sym);
                break;
            case NUMBER:
                fprintf(stderr,"%sNUMBER: %ld\n", getindent(indent), tree->val.num);
                break;
            case T:
                fprintf(stderr,"%sTRUE\n", getindent(indent));
                break;
            case F:
                fprintf(stderr,"%sFALSE\n", getindent(indent));
                break;
            default:
                fprintf(stderr,"%sWTF?\n", getindent(indent));
                break;
        }
        node_t *iter = tree->children;
        while (iter) {
            print_ast_full((tree_node_t*)iter->val, indent+2);
            iter = iter->next;
        }
    }
}

int main(int argc, char **argv) {
    ssize_t nr;
    size_t n = 0;
    char *buf = NULL;
    printf("melisp > ");
    nr = getline(&buf, &n, stdin);
    while (nr > 0) {
        node_t *tokens = tokenize(buf);
        print_tokens(tokens);
        tree_node_t *ast = parse(tokens);
        free_list(tokens, free);
        node_t *iter = ast->children;
        env_t *env = init_env();
        while(iter) {
            tree_node_t *this = eval_ast((tree_node_t*)iter->val, env);
            iter = iter->next;
            print_ast_full(this, 0);
        }
        free_tree(ast);
        free(buf);
        buf = NULL;
        printf("melisp > ");
        nr = getline(&buf, &n, stdin);
    }
    printf("\n");
    return 0;
}
