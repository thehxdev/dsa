#include <stdio.h>
#include "vector.h"

static inline int is_idx_valid(Vector *vp, size_t idx) {
    return (vp) ? (idx < vp->len) : 0;
}


Vector *vec_new(const size_t cap) {
    // new vector
    Vector *nv = (Vector*) malloc(sizeof(Vector));
    if (nv == NULL)
        return NULL;

    if (cap == 0)
        nv->cap = DEFAULT_CAP;
    else
        nv->cap = cap;

    nv->len  = 0;
    nv->vals = (int*) calloc(sizeof(int), nv->cap);
    if (nv->vals == NULL) {
        free(nv);
        return NULL;
    }

    return nv;
}


int *vec_get(Vector *vp, size_t idx) {
    return ((is_idx_valid(vp, idx)) ? &vp->vals[idx] : NULL);
}


void vec_free(Vector *vp) {
    if (vp == NULL)
        return;
    free(vp->vals);
    free(vp);
}


int vec_clean(Vector *vp) {
    if (vp == NULL || vp->vals == NULL)
        return 1;
    free(vp->vals);
    vp->len = 0;
    vp->vals = (int*) calloc(sizeof(int), vp->cap);
    if (vp->vals == NULL)
        return 2;
    return 0;
}


int vec_append(Vector *vp, int val) {
    if (vp == NULL)
        return 1;

    if (vp->len % vp->cap == 0) {
        size_t new_size = sizeof(int) * (vp->len + vp->cap);
        vp->vals = (int*) realloc(vp->vals, new_size);
        if (vp->vals == NULL)
            return 1;
    }

    vp->vals[vp->len] = val;
    vp->len += 1;
    return 0;
}


int vec_swap(Vector *vp, size_t idx1, size_t idx2) {
    if (!is_idx_valid(vp, idx1) || !is_idx_valid(vp, idx2))
        return 1;

    int tmp = *vec_get(vp, idx1);
    vp->vals[idx1] = *vec_get(vp, idx2);
    vp->vals[idx2] = tmp;
    return 0;
}


int vec_change(Vector *vp, size_t idx, int val) {
    if (!is_idx_valid(vp, idx))
        return 1;

    vp->vals[idx] = val;
    return 0;
}


int *vec_pop(Vector *vp) {
    if (vp == NULL || vp->len == 0)
        return NULL;

    int *last_val = vec_get(vp, vp->len - 1);
    vp->len -= 1;

    if (vp->len % vp->cap == 0) {
        size_t new_size = sizeof(int*) * (vp->len - vp->cap);
        vp->vals = (int*) realloc(vp->vals, new_size);
    }

    return last_val;
}


void vec_print(Vector *vp) {
    if (vp == NULL)
        return;
    printf("Vector = { ");
    for (size_t i = 0; i < vp->len; i++)
        printf("%d ", *vec_get(vp, i));
    printf("}\n");
}
