#ifndef ML_VECTOR_H
#define ML_VECTOR_H

#include <stdio.h>
#include <stdlib.h>

struct vector {
    void **data;
    size_t length;
    size_t capacity;
};
typedef struct vector vector_t;

vector_t *create_vector(size_t);
void append(vector_t*, void*);
void free_vector(vector_t*v, void(*)(void*));

#endif
