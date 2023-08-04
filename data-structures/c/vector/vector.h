#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <stdbool.h>


// Vector's default capacity
#define DEFAULT_CAP 20

// Simple and ready to use macros
#define VTOI(intptr) (*(int*)(intptr))    // void pointer to int
#define VTOD(intptr) (*(double*)(intptr)) // void pointer to double
#define VTOC(charptr) (*(char*)(charptr)) // void pointer to char
#define VTOS(strptr) ((char*)(strptr))    // void pointer to char* (string)

#define CHECH_AND_FREE(ptr) if ((ptr) != NULL) free((ptr))


struct __element {
    void *data;
    size_t size;
};
typedef struct __element Element;


struct __vector {
    // vector length
    size_t len;

    // vector capacity
    size_t cap;

    // list of Element pointers
    Element **elems;
};
typedef struct __vector Vector;


static bool check_idx(Vector *vp, size_t idx) {
    if (vp == NULL)
        return false;

    return (idx < vp->len);
}


/**
 * Create and initialize a new vector
 */
Vector *vec_new() {
    // new vector
    Vector *nv = (Vector*) malloc(sizeof(Vector));
    if (nv == NULL)
        return NULL;

    nv->len   = 0;
    nv->cap   = DEFAULT_CAP;
    nv->elems = (Element**) calloc(sizeof(Element*), nv->cap);
    if (nv->elems == NULL) {
        CHECH_AND_FREE(nv);
        return NULL;
    }

    return nv;
}


/**
 * Get data stored in an Element from vector
 */
void *vec_getData(Vector *vp, size_t idx) {
    if (!check_idx(vp, idx))
        return NULL;

    return vp->elems[idx]->data;
}


/**
 * Get an Element stored in vector
 */
Element *vec_getElement(Vector *vp, size_t idx) {
    if (!check_idx(vp, idx)) {
        return NULL;
    }

    return vp->elems[idx];
}


/**
 * Free and delete a vector from memory
 */
int vec_free(Vector *vp) {
    if (vp == NULL)
        return 1;

    if (vp->elems) {
        for (uint32_t i = 0; i < vp->len; i++) {
            CHECH_AND_FREE(vp->elems[i]->data);
            CHECH_AND_FREE(vp->elems[i]);
        }
        free(vp->elems);
        free(vp);
    }
    return 0;
}


/*
 * Clear a vector and re-initialize it
 */
int vec_clean(Vector *vp) {
    if (vp == NULL)
        return 1;

    if (vp->elems) {
        for (uint32_t i = 0; i < vp->len; i++) {
            CHECH_AND_FREE(vp->elems[i]->data);
            CHECH_AND_FREE(vp->elems[i]);
        }
        free(vp->elems);

        vp->len   = 0;
        vp->cap   = DEFAULT_CAP;
        vp->elems = (Element**) calloc(sizeof(Element*), vp->cap);
        if (vp->elems == NULL)
            return 1;
    }
    return 0;
}


/**
 * Append a new value to vector
 */
int vec_append(Vector *vp, void *val, size_t size) {
    if (vp == NULL || val == NULL || size == 0)
        return 1;

    if (vp->len % vp->cap == 0) {
        size_t new_size = sizeof(Element*) * (vp->len + vp->cap);
        vp->elems = (Element**) realloc(vp->elems, new_size);
        if (vp->elems == NULL)
            return 1;
    }

    vp->elems[vp->len] = (Element*) malloc(sizeof(Element));
    if (vp->elems[vp->len] == NULL)
        return 1;

    vp->elems[vp->len]->data = (void*) malloc(size);
    if (vp->elems[vp->len]->data == NULL)
        return 1;

    memcpy(vp->elems[vp->len]->data, val, size);
    vp->elems[vp->len]->size = size;
    
    vp->len += 1;
    return 0;
}


/**
 * Swap tow elements in vector
 */
int vec_swap(Vector *vp, size_t idx1, size_t idx2) {
    if (!check_idx(vp, idx1) || !check_idx(vp, idx2))
        return 1;

    Element *tmp = vec_getElement(vp, idx1);
    vp->elems[idx1] = vec_getElement(vp, idx2);
    vp->elems[idx2] = tmp;
    return 0;
}


/**
 * Set a new value to an element in vector
 */
int vec_change(Vector *vp, size_t idx, void *val, size_t size) {
    if (!check_idx(vp, idx) || val == NULL || size == 0)
        return 1;

    vp->elems[idx]->data = (void*) realloc(vp->elems[idx]->data, size);
    if (vp->elems[idx]->data == NULL)
        return 1;

    memmove(vp->elems[idx]->data, val, size);
    vp->elems[idx]->size = size;
    return 0;
}


/**
 * Remove last element from vector and return it
 */
Element *vec_pop(Vector *vp) {
    if (vp == NULL)
        return NULL;
    if (vp->len == 0)
        return NULL;

    Element *last_element = vec_getElement(vp, vp->len - 1);
    vp->elems[vp->len - 1] = NULL;
    vp->len -= 1;

    if (vp->len % vp->cap == 0) {
        size_t new_size = sizeof(Element*) * (vp->len - vp->cap);
        vp->elems = (Element**) realloc(vp->elems, new_size);
    }

    return last_element;
}

#endif // VECTOR_H
