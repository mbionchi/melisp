#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokenize.h"
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

token_t *parse_token(char *str) {
    token_t *token = malloc(sizeof(token_t));
    if (is_number(str)) {
        token->type = T_NUMBER;
        token->val.num = atoi(str);
    } else if (!strcmp(str, "#t")) {
        token->type = T_T;
    } else if (!strcmp(str, "#f")) {
        token->type = T_F;
    } else {
        token->val.sym = realloc(str, strlen(str));
        token->type = T_SYMBOL;
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
    int quote=0;
    while (*s_iter) {
        if (*s_iter == '(') {
            if (!i) {
                token_t *t = malloc(sizeof(token_t));
                t->type = T_LPAREN;
                prev = append(&iter, t);
                quote=0;
            } else {
                printf("expected whitespace between token and LPAREN\n");
                exit(1);
            }
        } else if (*s_iter == ')') {
            if (i) {
                str[i] = '\0';
                prev = append(&iter, parse_token(str));
                str = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
            token_t *t = malloc(sizeof(token_t));
            t->type = T_RPAREN;
            prev = append(&iter, t);
            quote=0;
        } else if (isspace(*s_iter) && !quote) {
            if (i) {
                str[i] = '\0';
                prev = append(&iter, parse_token(str));
                str = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
        } else if (*s_iter == '\'') {
            if (!i) {
                token_t *t = malloc(sizeof(token_t));
                t->type = T_QUOTE;
                prev = append(&iter, t);
                quote=1;
            } else {
                printf("expected whitespace between token and QUOTE\n");
                exit(1);
            }
        } else if (isgraph(*s_iter) &&
                *s_iter != ')' && *s_iter != '(' && *s_iter != '\'') {
            str[i] = *s_iter;
            i++;
            if (i > BUFSIZE-1) {
                printf("token too long\n");
                exit(1);
            }
            quote=0;
        } else {
            printf("unexpected character: %c\n", *s_iter);
            exit(1);
        }
        s_iter++;
    }
    prev->next = NULL;
    free(iter);
    return first;
}
