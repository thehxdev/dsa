#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdbool.h>


// Vector's default capacity
#define DEFAULT_CAP 20


typedef struct __vector {
    // vector length
    size_t len;

    // vector capacity
    size_t cap;

    // list of values
    int *vals;
} Vector;


/**
 * Create and initialize a new vector
 *
 * @cap: capacity of Vector
 *
 * @ret: pointer to new Vector
 */
Vector *vec_new(const size_t cap);


/**
 * Get value from vector
 */
int *vec_get(Vector *vp, size_t idx);


/**
 * Free and delete a vector from memory
 */
void vec_free(Vector *vp);


/*
 * Clear a vector and re-initialize it
 */
int vec_clean(Vector *vp);


/**
 * Append a new value to vector
 */
int vec_append(Vector *vp, int val);


/**
 * Swap tow elements in vector
 */
int vec_swap(Vector *vp, size_t idx1, size_t idx2);


/**
 * Set a new value to an element in vector
 */
int vec_change(Vector *vp, size_t idx, int val);


/**
 * Remove last element from vector and return it
 */
int *vec_pop(Vector *vp);


/**
 * Print a vector
 */
void vec_print(Vector *vp);

#endif // VECTOR_H
