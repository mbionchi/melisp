#ifndef ML_TOKENIZE_H
#define ML_TOKENIZE_H

#include "list.h"

enum token_type {LPAREN, RPAREN, SYMBOL, NUMBER, T, F};
typedef enum token_type token_type_t;

struct token {
    void *value;
    token_type_t type;
};
typedef struct token token_t;

node_t *tokenize(char*);
void free_token(void*);

#endif
