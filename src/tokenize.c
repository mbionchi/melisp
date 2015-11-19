#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "tokenize.h"

#define BUFSIZE 255

const char* LEXTYPE[] = {"LPAREN","RPAREN","ATOM"};

token_t **tokenize(char *s) {
    token_t **tokens;
    node_t *first, *iter;
    first = malloc(sizeof(node_t));
    iter = first;
    unsigned int n_tokens = 0;
    char *s_iter = s;
    char *lexeme = malloc(sizeof(char)*BUFSIZE);
    int i=0;
    *lexeme = '\0';
    while (*s_iter) {
        if (*s_iter == '(') {
            token_t *t = malloc(sizeof(token_t));
            t->lexeme = malloc(sizeof(char)*2);
            t->lexeme[0] = '(';
            t->lexeme[1] = '\0';
            t->type = LPAREN;
            iter->val = t;
            iter->next = malloc(sizeof(node_t));
            iter = iter->next;
            iter->next = NULL;
            n_tokens++;
        } else if (*s_iter == ')') {
            if (i) {
                token_t *t = malloc(sizeof(token_t));
                lexeme[i] = '\0';
                t->lexeme = lexeme;
                t->type = ATOM;
                iter->val = t;
                iter->next = malloc(sizeof(node_t));
                iter = iter->next;
                iter->next = NULL;
                n_tokens++;
                lexeme = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
            token_t *t = malloc(sizeof(token_t));
            t->lexeme = malloc(sizeof(char)*2);
            t->lexeme[0] = ')';
            t->lexeme[1] = '\0';
            t->type = RPAREN;
            iter->val = t;
            iter->next = malloc(sizeof(node_t));
            iter = iter->next;
            iter->next = NULL;
            n_tokens++;
        } else if (isspace(*s_iter)) {
            if (i) {
                token_t *t = malloc(sizeof(token_t));
                lexeme[i] = '\0';
                t->lexeme = lexeme;
                t->type = ATOM;
                iter->val = t;
                iter->next = malloc(sizeof(node_t));
                iter = iter->next;
                iter->next = NULL;
                n_tokens++;
                lexeme = malloc(sizeof(char)*BUFSIZE);
                i = 0;
            }
        } else {
            lexeme[i] = *s_iter;
            i++;
            if (i > BUFSIZE-1) {
                fprintf(stderr, "oh no! token too long\n");
                exit(1);
            }
        }
        s_iter++;
    }
    tokens = malloc(sizeof(token_t*)*n_tokens+1);
    iter = first;
    i = 0;
    while (iter) {
        tokens[i] = iter->val;
        iter = iter->next;
        i++;
    }
    tokens[n_tokens] = NULL;    /* we shall terminate the array with NULL */
    return tokens;
}

void free_tokens(token_t **t) {
    token_t **iter = t, **tmp;
    while (*iter) {
        tmp = iter;
        free((*tmp)->lexeme);
        free(*tmp);
        iter++;
    }
    free(t);
}
