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
    int *vals;
} Stack;


Stack *stk_new(const size_t cap);

int stk_push(Stack *sp, int val);

int stk_pop(Stack *sp);

void stk_popD(Stack *sp);

void stk_free(Stack *sp);

#endif // STACK_A_H
