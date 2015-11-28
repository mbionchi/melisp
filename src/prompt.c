#include <stdio.h>
#include <stdlib.h>

#include "tokenize.h"
#include "list.h"

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
        freelist(tokens, free_token);
        free(buf);
        buf = NULL;
        printf("melisp > ");
        nr = getline(&buf, &n, stdin);
    }
    printf("\n");
    return 0;
}
