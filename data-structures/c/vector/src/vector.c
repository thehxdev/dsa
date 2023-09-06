#include "vector.h"


static bool check_idx(Vector *vp, size_t idx) {
    if (vp == NULL)
        return false;

    return (idx < vp->len);
}


Vector *vec_new(enum v_type type) {
    // new vector
    Vector *nv = (Vector*) malloc(sizeof(Vector));
    if (nv == NULL)
        return NULL;

    nv->type = type;
    nv->len  = 0;
    nv->cap  = DEFAULT_CAP;
    nv->vals = (void**) calloc(sizeof(void*), nv->cap);
    if (nv->vals == NULL) {
        free(nv);
        return NULL;
    }

    return nv;
}


void *vec_get(Vector *vp, size_t idx) {
    if (!check_idx(vp, idx))
        return NULL;

    return vp->vals[idx];
}


void vec_free(Vector *vp, void (*fn)(void *p)) {
    if (vp == NULL)
        return;

    if (vp->vals) {
        for (uint32_t i = 0; i < vp->len; i++) {
            if (vp->vals[i])
                fn(vp->vals[i]);
        }
        free(vp->vals);
        free(vp);
    }
}


int vec_clean(Vector *vp, void (*fn)(void *p)) {
    if (vp == NULL)
        return 1;

    if (vp->vals) {
        for (uint32_t i = 0; i < vp->len; i++) {
            fn(vp->vals[i]);
        }
        free(vp->vals);

        vp->len   = 0;
        vp->cap   = DEFAULT_CAP;
        vp->vals = (void**) calloc(sizeof(void*), vp->cap);
        if (vp->vals == NULL)
            return 1;
    }
    return 0;
}


int vec_append(Vector *vp, void *val, size_t size) {
    if (vp == NULL || val == NULL)
        return 1;

    if (vp->len % vp->cap == 0) {
        size_t new_size = sizeof(void*) * (vp->len + vp->cap);
        vp->vals = (void**) realloc(vp->vals, new_size);
        if (vp->vals == NULL)
            return 1;
    }

    if (vp->type == JustVal) {
        vp->vals[vp->len] = (void*) malloc(size);
        if (vp->vals[vp->len] == NULL)
            return 1;
        memmove(vp->vals[vp->len], val, size);
    }
    else if (vp->type == JustPtr) {
        vp->vals[vp->len] = val;
    }

    vp->len += 1;
    return 0;
}


int vec_swap(Vector *vp, size_t idx1, size_t idx2) {
    if (!check_idx(vp, idx1) || !check_idx(vp, idx2))
        return 1;

    void *tmp = vec_get(vp, idx1);
    vp->vals[idx1] = vec_get(vp, idx2);
    vp->vals[idx2] = tmp;
    return 0;
}


int vec_change(Vector *vp, size_t idx, void *val, size_t size) {
    if (!check_idx(vp, idx) || val == NULL || size == 0)
        return 1;

    vp->vals[idx] = (void*) realloc(vp->vals[idx], size);
    if (vp->vals[idx] == NULL)
        return 1;

    memmove(vp->vals[idx], val, size);
    return 0;
}


void *vec_pop(Vector *vp) {
    if (vp == NULL)
        return NULL;
    if (vp->len == 0)
        return NULL;

    void *last_val = vec_get(vp, vp->len - 1);
    vp->vals[vp->len - 1] = NULL;
    vp->len -= 1;

    if (vp->len % vp->cap == 0) {
        size_t new_size = sizeof(void*) * (vp->len - vp->cap);
        vp->vals = (void**) realloc(vp->vals, new_size);
    }

    return last_val;
}


char *to_str(const char *str) {
    if (str == NULL)
        return NULL;

    char *tmp = (char*) malloc(strlen(str));
    if (tmp == NULL)
        return NULL;
    strcpy(tmp, str);

    return tmp;
}
