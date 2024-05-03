#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>
#include "array.h"

// #define xfree(p) do { free((p)); (p) = NULL;  } while (0)
void xfree(void *p) {
    free(p);
    p = NULL;
}


// generate a random number between @lower and @upper (inclusive)
long gen_rand(long lower, long upper) {
    long rand_num = (rand() % (upper - lower + 1)) + lower;
    return rand_num;
}


// create a new dynamic array
List *list_new(const size_t cap, free_func fn) {
    List *l = (List*) malloc(sizeof(List));
    if (l == NULL)
        return NULL;

    *l = (List) {
        .vals = NULL,
        .cap  = cap,
        .len  = 0,
        .val_free_fn = fn,
    };

    return l;
}


// free a dynamic array
void list_free(void *lp) {
    List *l = (List*)lp;
    if (l) {
        for (size_t i = 0; i < l->len; i++)
            l->val_free_fn(l->vals[i]);
        xfree(l->vals);
        xfree(l);
    }
}


// append to array
int list_append(List *lp, void *val, size_t bytes) {
    if (lp == NULL)
        return 1;

    // if length of array is divisible by it's capacity,
    // grow it's size by it's capacity
    if (lp->len % lp->cap == 0) {
        size_t new_size = sizeof(void*) * (lp->len + lp->cap);
        lp->vals = (void**) realloc(lp->vals, new_size);
        if (lp->vals == NULL) {
            list_free(lp);
            return 1;
        }
    }

    void **tmp = &lp->vals[lp->len];
    *tmp = malloc(bytes);
    memmove(*tmp, val, bytes);
    lp->len += 1;

    return 0;
}


// break an array into smaller arrays with maximum length of @max_len
// while each chunk has a random lenght
List *list_breakdown_rand(List *lp, const size_t max_len) {
    if (lp->len <= max_len)
        return lp;

    size_t right = 0, left = 0; // right and left pointer
    List *super_list = list_new(20, list_free); // super list to store smaller lists
    List *tmp = NULL; // tmp list to create small lists
    while (right < lp->len) {
        left = (size_t) gen_rand(right, right + max_len - 1);
        if (left >= lp->len)
            left = lp->len - 1;
        else if (left == right)
            continue; // don't create empty lists

        tmp = list_new(max_len + 1, xfree);
        for (size_t i = right; i <= left; i++)
            list_append(tmp, lp->vals[i], sizeof(int));

        // Just store the `tmp` list as pointer and not all of it
        list_append(super_list, tmp, sizeof(List));

        // free tmp list but NOT it's data
        // because we need it in super list
        xfree(tmp);
        right = left + 1;
    }

    return super_list;
}


List *list_merge_inner(List *lp) {
    if (!lp)
        return NULL;

    size_t i, j;
    List *tmp, *new = list_new(25, xfree);
    for (i = 0; i < lp->len; i++) {
        tmp = (List*) lp->vals[i];
        for (j = 0; j < tmp->len; j++)
            list_append(new, tmp->vals[j], sizeof(int));
    }

    return new;
}
