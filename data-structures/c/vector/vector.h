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
    return (idx < vp->len) ? true : false;
}


/**
 * Create and initialize a new vector
 */
Vector *vec_new() {
    // new vector
    Vector *nv = (Vector*) malloc(sizeof(Vector));

    nv->len   = 0;
    nv->cap   = DEFAULT_CAP;
    nv->elems = (Element**) calloc(sizeof(Element*), nv->cap);

    return nv;
}


/**
 * Get data stored in an Element from vector
 */
void *vec_getData(Vector *vp, size_t idx) {
    if (check_idx(vp, idx)) {
        return vp->elems[idx]->data;
    }

    return NULL;
}


/**
 * Get an Element stored in vector
 */
Element *vec_getElement(Vector *vp, size_t idx) {
    if (check_idx(vp, idx)) {
        return vp->elems[idx];
    }

    return NULL;
}


/**
 * Free and delete a vector from memory
 */
void vec_free(Vector *vp) {
    if (vp->elems && vp) {
        for (uint32_t i = 0; i < vp->len; i++) {
            free(vp->elems[i]->data);
            free(vp->elems[i]);
        }
        free(vp->elems);

        free(vp);
    }
}


/*
 * Clear a vector and re-initialize it
 */
void vec_clean(Vector *vp) {
    if (vp->elems && vp) {
        for (uint32_t i = 0; i < vp->len; i++) {
            free(vp->elems[i]->data);
            free(vp->elems[i]);
        }
        free(vp->elems);

        vp->len   = 0;
        vp->cap   = DEFAULT_CAP;
        vp->elems = (Element**) calloc(sizeof(Element*), vp->cap);
    }
}


/**
 * Append a new value to vector
 */
int vec_append(Vector *vp, void *val, size_t size) {
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
void vec_swap(Vector *vp, size_t idx1, size_t idx2) {
    if (check_idx(vp, idx1), check_idx(vp, idx2)) {
        Element *tmp = vec_getElement(vp, idx1);
        vp->elems[idx1] = vec_getElement(vp, idx2);
        vp->elems[idx2] = tmp;
    }
}


/**
 * Set a new value to an element in vector
 */
int vec_set(Vector *vp, size_t idx, void *val, size_t size) {
    if (check_idx(vp, idx)) {
        if (vp->elems[idx])
            free(vec_getElement(vp, idx));

        if (vp->elems[idx]->data)
            free(vec_getData(vp, idx));

        vp->elems[idx] = (Element*) malloc(sizeof(Element));
        if (vp->elems[idx] == NULL)
            return 1;

        vp->elems[idx]->data = (void*) malloc(size);
        if (vp->elems[idx]->data == NULL)
            return 1;

        memcpy(vp->elems[idx]->data, val, size);
        vp->elems[idx]->size = size;
        return 0;
    }
    return 1;
}


/**
 * Remove last element from vector and return it
 */
Element *vec_pop(Vector *vp) {
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
