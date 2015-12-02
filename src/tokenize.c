#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokenize.h"
#include "parse.h"
#include "list.h"

#define BUFSIZE 255

int is_number(char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0;
        }
        str++;
    }
    return 1;
}

token_t *parse_atom(char *str) {
    token_t *token = malloc(sizeof(token_t));
    if (is_number(str)) {
        token->type = NUMBER;
        int *numpt = malloc(sizeof(int));
        *numpt = atoi(str);
        token->value = numpt;
    } else if (!strcmp(str, "#t")) {
        token->value = NULL;
        token->type = T;
    } else if (!strcmp(str, "#f")) {
        token->value = NULL;
        token->type = F;
    } else {
        token->value = realloc(str, strlen(str));
        token->type = SYMBOL;
    }
    return token;
}

node_t *tokenize(char *s_iter) {
    node_t *first, *iter, *prev;
    first = malloc(sizeof(node_t));
    prev = NULL;
    iter = first;
    char *str = malloc(sizeof(char)*BUFSIZE);
    *str = '\0';
    int i=0;
    while (*s_iter) {
        if (*s_iter == '(') {
            if (i) {
                str[i] = '\0';
                prev = append(&iter, parse_atom(str));
                str = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
            token_t *t = malloc(sizeof(token_t));
            t->value = NULL;
            t->type = LPAREN;
            prev = append(&iter, t);
        } else if (*s_iter == ')') {
            if (i) {
                str[i] = '\0';
                prev = append(&iter, parse_atom(str));
                str = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
            token_t *t = malloc(sizeof(token_t));
            t->value = NULL;
            t->type = RPAREN;
            prev = append(&iter, t);
        } else if (isspace(*s_iter)) {
            if (i) {
                str[i] = '\0';
                prev = append(&iter, parse_atom(str));
                str = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
        } else if (isgraph(*s_iter) && *s_iter != ')' && *s_iter != '(') {
            str[i] = *s_iter;
            i++;
            if (i > BUFSIZE-1) {
                fprintf(stderr, "oh no! token too long\n");
                exit(1);
            }
        } else {
            fprintf(stderr, "lexer err: unexpected character\n");
            exit(1);
        }
        s_iter++;
    }
    prev->next = NULL;
    free(iter);
    return first;
}

void free_token(void *t) {
    free(((token_t*)t)->value);
    free(t);
}
