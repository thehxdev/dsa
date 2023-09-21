#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List *list_new(const size_t cap) {
    List *l = (List*) malloc(sizeof(List));
    l->cap = cap;
    l->len = 0;

    l->nums = (int*) malloc(sizeof(int) * cap);
    if (!l->nums) {
        free(l);
        return NULL;
    }

    return l;
}


void list_free(List *lp) {
    if (lp) {
        if (lp->nums)
            free(lp->nums);
        free(lp);
    }
}


void list_append(List *lp, int val) {
    if (!lp)
        return;

    if (!(lp->len % lp->cap)) {
        size_t new_size = sizeof(int) * (lp->len + lp->cap);
        lp->nums = (int*) realloc(lp->nums, new_size);
        if (!lp->nums) {
            list_free(lp);
            return;
        }
    }

    lp->nums[lp->len] = val;
    lp->len += 1;
}


void list_print(List *lp) {
    if (lp) {
        printf("list = { ");
        for (size_t i = 0; i < lp->len; i++)
            printf("%d ", lp->nums[i]);
        printf("}\n");
    }
}
