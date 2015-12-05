#include <stdio.h>
#include <stdlib.h>

#include "tokenize.h"
#include "list.h"
#include "parse.h"
#include "eval.h"

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
            case T_LPAREN:
                printf("LEXER: LPAREN\n");
                break;
            case T_RPAREN:
                printf("LEXER: RPAREN\n");
                break;
            case T_SYMBOL:
                printf("LEXER: SYMBOL %s\n", token->val.sym);
                break;
            case T_NUMBER:
                printf("LEXER: NUMBER %ld\n", token->val.num);
                break;
            case T_T:
                printf("LEXER: TRUE\n");
                break;
            case T_F:
                printf("LEXER: FALSE\n");
                break;
            case T_QUOTE:
                printf("LEXER: QUOTE\n");
                break;
            default:
                printf("WTF???\n");
                break;
        }
        iter = iter->next;
    }
}

void print_ast(tree_node_t *tree) {
    if (tree) {
        node_t *iter;
        switch (tree->type) {
            case P_PROGRAM:
                iter = tree->children;
                while (iter) {
                    print_ast((tree_node_t*)iter->val);
                    printf("\n");
                    iter = iter->next;
                }
                break;
            case P_SYMBOL:
                printf("%s", (char*)tree->val);
                break;
            case P_NUMBER:
                printf("%d", *(int*)tree->val);
                break;
            case P_LIST:
                printf("(");
                iter = tree->children;
                if (iter) {
                    print_ast((tree_node_t*)iter->val);
                    iter = iter->next;
                }
                while (iter) {
                    printf(" ");
                    print_ast((tree_node_t*)iter->val);
                    iter = iter->next;
                }
                printf(")");
                break;
            case P_T:
                printf("#t");
                break;
            case P_F:
                printf("#f");
                break;
            default:
                printf("WTF???");
                break;
        }
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
            print_ast_types((tree_node_t*)iter->val, indent+2);
            iter = iter->next;
        }
    }
}

int main(int argc, char **argv) {
    ssize_t nr;
    size_t n = 0;
    char *buf = NULL;
    printf("melisp > ");
    nr = getline(&buf, &n, stdin);
    while (nr > 0) {
        node_t *tokens = tokenize(buf);
        print_tokens(tokens);
//        tree_node_t *ast = parse(tokens);
//        print_ast_types(ast, 0);
//        eval_ast(&ast, NULL);
//        print_ast_types(ast, 0);
//        print_ast(ast);
//        freetree(ast, freedummy); /* deletion of vals is handled by freelist call,
//                                     since in the ast vals are a shallow copies */
//        freelist(tokens, free_token);
        free(buf);
        buf = NULL;
        printf("melisp > ");
        nr = getline(&buf, &n, stdin);
    }
    printf("\n");
    return 0;
}
