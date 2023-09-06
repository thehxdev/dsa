#ifndef VECTOR_H
#define VECTOR_H

#define __USE_GNU
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>
#include <stdbool.h>


// Vector's default capacity
#define DEFAULT_CAP 20

// Simple and ready to use macros for type casting
// common types from void*
#define VTOI(p) (*(int*)(p))    // void pointer to int
#define VTOD(p) (*(double*)(p)) // void pointer to double
#define VTOC(p) (*(char*)(p))   // void pointer to char
#define VTOS(p) ((char*)(p))    // void pointer to char* (string)


enum v_type {
    JustPtr,
    JustVal,
};

typedef struct __vector {
    // vector length
    size_t len;

    // vector capacity
    size_t cap;

    // list of values
    void **vals;

    // type of vector (how store data)
    enum v_type type;
} Vector;


/**
 * Create and initialize a new vector
 */
Vector *vec_new(enum v_type type);


/**
 * Get value from vector
 */
void *vec_get(Vector *vp, size_t idx);


/**
 * Free and delete a vector from memory
 */
void vec_free(Vector *vp, void (*fn)(void *p));


/*
 * Clear a vector and re-initialize it
 */
int vec_clean(Vector *vp, void (*fn)(void *p));


/**
 * Append a new value to vector
 */
int vec_append(Vector *vp, void *val, size_t size);


/**
 * Swap tow elements in vector
 */
int vec_swap(Vector *vp, size_t idx1, size_t idx2);


/**
 * Set a new value to an element in vector
 */
int vec_change(Vector *vp, size_t idx, void *val, size_t size);


/**
 * Remove last element from vector and return it
 */
void *vec_pop(Vector *vp);


/**
 * Convert a string to a malloc'd string
 *
 * @str: input string
 *
 * @ret: malloc'd string
 */
char *to_str(const char *str);

#endif // VECTOR_H
