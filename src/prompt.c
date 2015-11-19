#include <stdio.h>
#include <stdlib.h>

#include "tokenize.h"

void print_tokens(token_t **t) {
    token_t **iter = t;
    while (*iter) {
        printf("LEXEME \'%s\' TYPE %s\n", (*iter)->lexeme, LEXTYPE[(*iter)->type]);
        iter++;
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
        token_t **tokens = tokenize(buf);
        print_tokens(tokens);
        free_tokens(tokens);
        free(buf);
        buf = NULL;
        printf("melisp > ");
        nr = getline(&buf, &n, stdin);
    }
    printf("\n");
    return 0;
}
