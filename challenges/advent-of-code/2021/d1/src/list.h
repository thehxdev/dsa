#ifndef AOC_2021_D1_LIST_H
#define AOC_2021_D1_LIST_H


#include <stddef.h>


typedef struct __list {
    int *nums;
    size_t len;
    size_t cap;
} List;


List *list_new(const size_t cap);

void list_free(List *lp);

void list_append(List *lp, int val);

void list_print(List *lp);

#endif // AOC_2021_D1_LIST_H
