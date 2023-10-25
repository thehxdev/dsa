#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define LIST_DEFAULT_CAP 20

List *list_new(const size_t cap) {
    List *l = (List*) malloc(sizeof(List));
    if (l == NULL)
        return NULL;

    l->len = 0;
    l->cap = (cap == 0) ? LIST_DEFAULT_CAP : cap;

    l->vals = (int*) malloc(sizeof(int) * l->cap);
    if (l->vals == NULL) {
        free(l);
        return NULL;
    }

    return l;
}


void list_free(List *lp) {
    if (lp) {
        if (lp->vals != NULL) free(lp->vals);
        free(lp);
    }
}


void list_append(List *lp, const int val) {
    if (lp == NULL)
        return;

    if (lp->len % lp->cap == 0) {
        size_t new_size = sizeof(int) * (lp->len + lp->cap);
        lp->vals = (int*) realloc(lp->vals, new_size);
        if (lp->vals == NULL) return;
    }

    lp->vals[lp->len] = val;
    lp->len += 1;
}


void list_set(List *lp, const size_t idx, const int val) {
    if (lp == NULL)
        return;
    if (idx >= lp->len)
        return;

    lp->vals[idx] = val;
}


void list_print(List *lp) {
    if (lp) {
        printf("[ ");
        for (size_t i = 0; i < lp->len; i++)
            printf("%d ", lp->vals[i]);
        printf("]\n");
    }
}


List *list_copy(List *src) {
    List *dest = list_new(src->cap);
    if (dest == NULL)
        return NULL;

    for (size_t i = 0; i < src->len; i++)
        list_append(dest, src->vals[i]);

    return dest;
}
