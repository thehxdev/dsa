/*
 * Stack implementation using array
 */


#ifndef STACK_A_H
#define STACK_A_H

#define DEFAULT_CAP 20

#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

typedef struct __stack {
    size_t cap;
    size_t len;
    void **elems;
} Stack;


Stack *stk_new() {
    // new stack
    Stack *ns = (Stack*) malloc(sizeof(Stack));
    if (ns == NULL)
        return NULL;

    ns->elems = (void**) calloc(sizeof(void*), DEFAULT_CAP);
    if (ns->elems == NULL) {
        free(ns);
        return NULL;
    }

    ns->cap = DEFAULT_CAP;
    ns->len = 0;

    return ns;
}


int stk_push(Stack *sp, void *val, size_t size) {
    if (sp == NULL || val == NULL || size == 0) {
        return 1;
    }

    if (sp->len % sp->cap == 0) {
        size_t new_size = sizeof(void*) * (sp->len + sp->cap);
        sp->elems = (void**) realloc(sp->elems, new_size);
    }

    if (sp->elems == NULL)
        return 1;

    sp->elems[sp->len] = (void*) malloc(size);
    if (sp->elems[sp->len] == NULL)
        return 1;

    memcpy(sp->elems[sp->len], val, size);
    sp->len += 1;

    return 0;
}


void *stk_pop(Stack *sp) {
    if (sp == NULL)
        return NULL;

    void *last_elem = sp->elems[sp->len - 1];
    sp->elems[sp->len - 1] = NULL;

    sp->len -= 1;
    if (sp->len % sp->cap == 0) {
        size_t new_size = sizeof(void*) * sp->len;
        sp->elems = (void**) realloc(sp->elems, new_size);
    }

    return last_elem;
}


void stk_popD(Stack *sp) {
    if (sp) {
        void *last_elem = sp->elems[sp->len - 1];
        if (last_elem)
            free(last_elem);
        sp->elems[sp->len - 1] = NULL;

        sp->len -= 1;
        if (sp->len % sp->cap == 0) {
            size_t new_size = sizeof(void*) * sp->len;
            sp->elems = (void**) realloc(sp->elems, new_size);
        }
    }
}


void stk_free(Stack *sp) {
    if (sp) {
        if (sp->elems) {
            for (uint32_t i = 0; i < sp->len; i++) {
                if (sp->elems[i])
                    free(sp->elems[i]);
            }
            free(sp->elems);
        }
        free(sp);
    }
}


#endif // STACK_A_H
