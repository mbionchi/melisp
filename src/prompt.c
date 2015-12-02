#include <stdio.h>
#include <stdlib.h>

#include "tokenize.h"
#include "list.h"
#include "parse.h"

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
            case LPAREN:
                printf("LEXER: LPAREN\n");
                break;
            case RPAREN:
                printf("LEXER: RPAREN\n");
                break;
            case SYMBOL:
                printf("LEXER: SYMBOL %s\n", (char*)token->value);
                break;
            case NUMBER:
                printf("LEXER: NUMBER %d\n", *((int*)token->value));
                break;
            case T:
                printf("LEXER: TRUE\n");
                break;
            case F:
                printf("LEXER: FALSE\n");
                break;
            default:
                printf("WTF???\n");
                break;
        }
        iter = iter->next;
    }
}

void print_ast_types(tree_node_t *tree, int indent) {
    if (!tree) {
        return;
    } else {
        switch (tree->type) {
            case P_PROGRAM:
                fprintf(stderr,"%sPROGRAM\n", getindent(indent));
                break;
            case P_SEXPR:
                fprintf(stderr,"%sSEXPR\n", getindent(indent));
                break;
            case P_LIST:
                fprintf(stderr,"%sLIST\n", getindent(indent));
                break;
            case P_SYMBOL:
                fprintf(stderr,"%sSYMBOL: %s\n", getindent(indent), (char*)tree->val);
                break;
            case P_NUMBER:
                fprintf(stderr,"%sNUMBER: %d\n", getindent(indent), *(int*)tree->val);
                break;
            case P_T:
                fprintf(stderr,"%sTRUE\n", getindent(indent));
                break;
            case P_F:
                fprintf(stderr,"%sFALSE\n", getindent(indent));
                break;
            default:
                fprintf(stderr,"%sWTF?\n", getindent(indent));
                break;
        }
        node_t *iter = tree->children;
        while (iter) {
            print_ast_types((tree_node_t*)iter->val, indent+4);
            iter = iter->next;
        }
    }
}

int main(int argc, char **argv) {
    ssize_t nr;
    size_t n = 0;
    char *buf;
    buf = NULL;
    printf("melisp > ");
    nr = getline(&buf, &n, stdin);
    while (nr > 0) {
        node_t *tokens = tokenize(buf);
        print_tokens(tokens);
        tree_node_t *ast = parse(tokens);
        print_ast_types(ast, 0);
        freelist(tokens, free_token);
        free(buf);
        buf = NULL;
        printf("melisp > ");
        nr = getline(&buf, &n, stdin);
    }
    printf("\n");
    return 0;
}
