#include "vector.h"

#include <stdio.h>

vector_t *create_vector(size_t n) {
    vector_t *v = malloc(sizeof(vector_t));
    v->data = malloc(sizeof(void*)*n);
    v->capacity = n;
    v->length = 0;
    return v;
}

void push_back(vector_t *v, void *elm) {
    if (v->capacity==0) {
        v->data=malloc(sizeof(void*));
        v->capacity=1;
    } else if (v->length==v->capacity) {
        v->data = realloc(v->data, sizeof(void*)*v->capacity*2);
        v->capacity *= 2;
    }
    void **iter = v->data+v->length;
    *iter = elm;
    v->length++;
}

void free_vector(vector_t *v, void(*f)(void*)) {
    void **iter;
    for (iter=v->data; iter<iter+v->length; iter++) {
        f(*iter);
    }
    free(v->data);
    free(v);
}
