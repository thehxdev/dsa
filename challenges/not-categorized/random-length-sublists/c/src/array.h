#ifndef ARRAY_H
#define ARRAY_H

#include <stddef.h>


typedef void (*free_func)(void*);

typedef struct __list {
    void **vals;
    size_t len;
    size_t cap;
    free_func val_free_fn;
} List;

void xfree(void *p);

long gen_rand(long lower, long upper);

List *list_new(const size_t cap, free_func fn);

void list_free(void *lp);

int list_append(List *lp, void *val, size_t bytes);

List *list_breakdown_rand(List *lp, const size_t max_len);

List *list_merge_inner(List *lp);

#endif // ARRAY_H
