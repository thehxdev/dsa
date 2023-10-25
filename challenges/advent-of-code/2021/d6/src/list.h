#ifndef LIST_H
#define LIST_H


#include <stddef.h>
#include <stdint.h>


typedef struct __list {
    int *vals;
    uint64_t len;
    size_t cap;
} List;


List *list_new(const size_t cap);

void list_free(List *lp);

void list_append(List *lp, const int val);

void list_set(List *lp, const size_t idx, const int val);

void list_print(List *lp);

List *list_copy(List *src);

#endif
