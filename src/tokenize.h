#ifndef ML_TOKENIZE_H
#define ML_TOKENIZE_H

enum token_type {LPAREN, RPAREN, ATOM};
typedef enum token_type token_type_t;

struct token {
    char *lexeme;
    token_type_t type;
};
typedef struct token token_t;

struct node {
    void *val;
    struct node *next;
};
typedef struct node node_t;

extern const char* LEXTYPE[];

token_t **tokenize(char*);
void free_tokens(token_t**);

#endif
