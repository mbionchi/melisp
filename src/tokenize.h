#ifndef ML_TOKENIZE_H
#define ML_TOKENIZE_H

#include "list.h"

enum token_type {T_LPAREN, T_RPAREN, T_SYMBOL, T_NUMBER, T_T, T_F, T_QUOTE};
typedef enum token_type token_type_t;

struct token {
    union {
        long int num;
        char *sym;
    } val;
    token_type_t type;
};
typedef struct token token_t;

node_t *tokenize(char*);
void free_token(void*);

#endif
