#ifndef ML_TOKENIZE_H
#define ML_TOKENIZE_H

#include "list.h"

enum token_type {T_LPAREN, T_RPAREN, T_SYMBOL, T_NUMBER, T_T, T_F};
typedef enum token_type token_type_t;

union ml_val {
    long int num;
    char * sym;
};
typedef union ml_val ml_val_t;

struct token {
    ml_val_t val;
    token_type_t type;
};
typedef struct token token_t;

node_t *tokenize(char*);

#endif
