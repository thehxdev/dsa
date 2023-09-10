#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include "stacka.h"


Stack *stk_new(const size_t cap) {
    Stack *ns = (Stack*) malloc(sizeof(Stack));
    if (ns == NULL)
        return NULL;

    size_t capacity = (cap == 0) ? DEFAULT_CAP : cap;
    ns->vals = (int*) calloc(sizeof(int), capacity);

    if (ns->vals == NULL) {
        free(ns);
        return NULL;
    }

    ns->cap = capacity;
    ns->len = 0;

    return ns;
}


int stk_push(Stack *sp, int val) {
    if (sp == NULL)
        return 1;

    if (sp->len % sp->cap == 0) {
        size_t new_size = sizeof(int) * (sp->len + sp->cap);
        sp->vals = (int*) realloc(sp->vals, new_size);
        if (sp->vals == NULL)
            return 1;
    }

    sp->vals[sp->len] = val;
    sp->len += 1;

    return 0;
}


int stk_pop(Stack *sp) {
    if (sp == NULL)
        return 0;

    int last_elem = sp->vals[sp->len - 1];

    if (sp->len % sp->cap == 0) {
        size_t new_size = sizeof(int) * sp->len;
        sp->vals = (int*) realloc(sp->vals, new_size);
    }
    sp->len -= 1;

    return last_elem;
}


void stk_popD(Stack *sp) {
    if (sp) {
        sp->vals[sp->len - 1] = 0;
        if (sp->len % sp->cap == 0) {
            size_t new_size = sizeof(int) * sp->len;
            sp->vals = (int*) realloc(sp->vals, new_size);
        }
        sp->len -= 1;
    }
}


void stk_free(Stack *sp) {
    if (sp) {
        free(sp->vals);
        free(sp);
    }
}
