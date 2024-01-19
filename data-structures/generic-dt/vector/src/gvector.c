#include <stdlib.h>
#include <memory.h>
#include "gvector.h"


static Val_t *val_new(void *val, size_t val_size) {
    Val_t *v = (Val_t*) malloc(sizeof(Val_t));
    if (is_null(v))
        return NULL;

    v->size = val_size;
    v->data = calloc(val_size, 1);
    if (is_null(v->data)) {
        free(v);
        return NULL;
    }
    memmove(v->data, val, val_size);

    return v;
}


GVec_t *gvec_new(size_t cap) {
    GVec_t *v = (GVec_t*) malloc(sizeof(GVec_t));
    if (is_null(v))
        return NULL;

    v->cap = (cap <= 0) ? GVEC_DEF_CAP : cap;
    v->len = 0;

    v->vals = (Val_t**) malloc(sizeof(Val_t*) * v->cap);
    if (is_null(v->vals)) {
        free(v);
        return NULL;
    }

    return v;
}


void gvec_free(GVec_t **gvp) {
    Val_t *v;
    GVec_t *tmp = *gvp;
    if (tmp) {
        for (size_t i = 0; i < tmp->len; i++) {
            v = tmp->vals[i];
            val_free(&v);
        }
        free(tmp->vals);
        free(tmp);
    }
}


int gvec_append(GVec_t *gvp, void *val, size_t val_size) {
    if (is_null(gvp) || is_null(val))
        return 1;

    if (gvp->len % gvp->cap == 0) {
        size_t extended_size = (gvp->len + gvp->cap) * sizeof(Val_t*);
        gvp->vals = (Val_t**) realloc(gvp->vals, extended_size);
        if (is_null(gvp->vals))
            return 1;
    }

    gvp->vals[gvp->len] = val_new(val, val_size);
    gvp->len += 1;
    return 0;
}


Val_t *gvec_pop(GVec_t *gvp) {
    if (gvp->len == 0)
        return NULL;
    size_t last_idx = gvp->len - 1;
    Val_t *last = gvp->vals[last_idx];

    gvp->vals[last_idx] = NULL;
    gvp->len -= 1;

    if (gvp->len % gvp->cap == 0) {
        size_t new_size = (gvp->len - gvp->cap) * sizeof(Val_t*);
        gvp->vals = (Val_t**) realloc(gvp->vals, new_size);
    }

    return last;
}


void *gvec_get(GVec_t *gvp, size_t idx) {
    if (idx >= gvp->len)
        return NULL;
    return gvp->vals[idx]->data;
}


void val_free(Val_t **vp) {
    Val_t *tmp = *vp;
    if (tmp) {
        check_then_free(tmp->data);
        free(tmp);
    }
}


