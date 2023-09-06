/*
 * Stack implementation using array
 */


#ifndef STACK_A_H
#define STACK_A_H

#define DEFAULT_CAP 20

#include <stddef.h>

typedef struct __stack {
    size_t cap;
    size_t len;
    void **elems;
} Stack;


Stack *stk_new();

int stk_push(Stack *sp, void *val, size_t size);

void *stk_pop(Stack *sp);

void stk_popD(Stack *sp);

void stk_free(Stack *sp);

#endif // STACK_A_H
