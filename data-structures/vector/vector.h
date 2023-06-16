#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>


#define cuint64 const u_int64_t
#define BYTES_OF_VOID(bytes) (sizeof(void **) * (bytes))
#define BYTES_OF_VECTOR(bytes) (sizeof(vector_t) * (bytes))
#define CHECK_IDX(vecptr, idx) (((idx) < (vecptr->length)) || ((idx) == 0))


#define VTOI(intptr) (*(int64_t *)(intptr)) /* void to int64_t */
#define VTOCH(charptr) (*(char *)(charptr)) /* void to char */
#define VTOS(strptr) ((char *)(strptr)) /* void to char* (str) */


/* vector types */
#define INT64_T 0
#define CHAR_T  1
#define STR_T   2
#define VOID_T  3

struct __vector {
    u_int64_t length;
    void **content;
    u_int8_t type;
};

typedef struct __vector vector_t;


/**
 * Create a new vector
 *
 * @param vector type
 * @ret a vector type instance
 */
vector_t vec_new(u_int8_t vec_type) {
    vector_t new_vec;
    new_vec.content = NULL;
    new_vec.length  = 0;
    new_vec.type    = vec_type;

    return new_vec;
}


/**
 * Initialize a vector pointer that allocated by malloc
 * This will wipe vector's content.
 *
 * @param pointer to a vector
 * @param vector type
 * @ret void
 */
void vecptr_init(vector_t *vec, u_int8_t vec_type) {
    if (vec->content)
        free(vec->content);
    vec->content = NULL;
    vec->length  = 0;
    vec->type    = vec_type;
}


/**
 * append an item with type vecT to the end of vector
 * 
 * @param pointer to a vector
 * @param pointer to a value
 * @param bytes of value (use `strlen()` for `STR_T` type)
 * @ret   0 if no error, 1 if error occures
 */
u_int8_t vec_append(vector_t *vec, void *value, cuint64 size) {
    if (vec->content) {
        u_int64_t new_size = vec->length + 1;
        vec->content = (void **) realloc(vec->content, BYTES_OF_VOID(new_size));
    }
    else
        vec->content = (void **) malloc(BYTES_OF_VOID(1));

    if (!vec->content)
        return 1;

    vec->content[vec->length] = (void *) malloc(size);
    memcpy(vec->content[vec->length], value, size);
    vec->length++;

    return 0;
}


/**
 * get an index's void pointer from vector
 *
 * @param pointer to a vector
 * @param an index
 * @ret   void pointer to a value or NULL
 */
void *vec_get(vector_t *vec, cuint64 idx) {
    if (CHECK_IDX(vec, idx))
        return ((void *) vec->content[idx]);
    return NULL;
}


/**
 * Remove an element at the end of the vector
 * and return it's void pointer.
 *
 * don't forget to call `free()` on returned value.
 *
 * @param pointer to a vector
 * @ret   void pointer to a value
 */
void *vec_pop(vector_t *vec) {
    if (vec->length > 0) {
        u_int64_t last_idx = vec->length - 1;
        u_int64_t new_size = vec->length - 1;
        void *idx_val = vec_get(vec, last_idx);
        vec->content[last_idx] = NULL;
        vec->content = (void **) realloc(vec->content, BYTES_OF_VOID(new_size));
        vec->length--;

        return idx_val;
    }
    return NULL;
}

/*
 * Remove an element at the end of the vector and call `free()` on it.
 *
 * @param pointer to a vector
 * @ret   void pointer to a value
 */
void vec_remove(vector_t *vec) {
    if (vec->length > 0) {
        u_int64_t last_idx = vec->length - 1;
        u_int64_t new_size = vec->length - 1;
        free(vec->content[last_idx]);
        vec->content = (void **) realloc(vec->content, BYTES_OF_VOID(new_size));
        vec->length--;

    }
}


/**
 * free up a vector's content.
 *
 * If vector contains elements that allocated on
 * the heap, it's your responsibility to free them
 * before calling this function.
 *
 * @param pointer to a vector
 * @ret   void
 */
void vec_delete(vector_t *vec) {
    if (vec->content) {
        for (u_int64_t i = 0; i < vec->length; i++)
            free(vec->content[i]);
        free(vec->content);
    }
}


/**
 * clean up a vector and make it empty
 *
 * @param pointer to a vector
 * @param new vector's type
 * @ret void
 */
void vec_clean(vector_t *vec, u_int8_t vec_type) {
    vec_delete(vec);
    vec->content = NULL;
    vec->length  = 0;
    vec->type    = vec_type;
}


/**
 * update an element to a new value
 *
 * @param pointer to a vector
 * @param an index
 * @param void pointer to a value
 * @param bytes of value (use `strlen()` for `STR_T` type)
 * @ret   0 if no error, 1 if error occures
 */
u_int8_t vec_set(vector_t *vec, cuint64 idx, void *val, cuint64 size) {
    if (CHECK_IDX(vec, idx)) {
        if (vec->content[idx]) free(vec->content[idx]);
        vec->content[idx] = (void *) malloc(size);
        memcpy(vec->content[idx], val, size);
        return 0;
    }
    return 1;
}


/**
 * swap tow elements in the vector
 *
 * @param pointer to a vector
 * @param index 1
 * @param index 2
 * @ret   void
 */
void vec_swap(vector_t *vec, cuint64 idx1, cuint64 idx2) {
    if ((CHECK_IDX(vec, idx1)) && (CHECK_IDX(vec, idx2))) {
        void *tmpval = vec->content[idx1];
        vec->content[idx1] = vec->content[idx2];
        vec->content[idx2] = tmpval;
    }
}


/**
 * reverse a vector
 *
 * @param pointer to a vector
 * @ret   void
 */
void vec_reverse(vector_t *vec) {
    void **buffer = (void **) malloc(BYTES_OF_VOID(vec->length));
    u_int64_t j = 0;

    for (int64_t i = (vec->length - 1); i >= 0; i--) {
        buffer[j] = vec_get(vec, i);
        j++;
    }

    for (u_int64_t i = 0; i < vec->length; i++) {
        vec->content[i] = buffer[i];
    }

    free(buffer);
}


// partition function for vec_sort (quicksort)
static int64_t partition(vector_t *vec, int64_t lower, int64_t upper) {
    int64_t i = (lower - 1);
    const int64_t pivot = VTOI(vec_get(vec, upper));

    for (int64_t j = lower; j < upper; j++) {
        if (VTOI(vec_get(vec, j)) <= pivot) {
            i++;
            vec_swap(vec, i, j);
        }
    }

    vec_swap(vec, i + 1, upper);
    return (i + 1);
}



/**
 * sort the vector (if vecT is not char*)
 *
 * @param pointer to vector
 * @param lower index (typically first item index (0))
 * @param upper index (typically last item index)
 * @ret   void
 */
void vec_sort(vector_t *vec, cuint64 lower, cuint64 upper) {
    // quicksort
    if (upper > lower) {
        int64_t partitionIndex = partition(vec, lower, upper);

        vec_sort(vec, lower, partitionIndex - 1);
        vec_sort(vec, partitionIndex + 1, upper);
    }
}



/**
 * copy src vector to dest
 * WARN: this function wipes dest vector!
 *
 * @param pointer to vector dest
 * @param pointer to vector src
 * @ret   void
*/
void vec_cpy(vector_t *dest, vector_t *src) {
    if (src->length > 0 && src->type == dest->type) {
        if (dest->content)
            vec_clean(dest, src->type);
        dest->content = (void **) malloc(BYTES_OF_VOID(src->length));

        dest->length = src->length;
        for (u_int64_t i = 0; i < src->length; i++) {
            if (src->type == STR_T) {
                vec_set(dest, i, vec_get(src, i), strlen(vec_get(src, i)));
                continue;
            }
            vec_set(dest, i, vec_get(src, i), sizeof(vec_get(src, i)));
        }
    }
}


/**
 * insert to a specific index in vector
 *
 * @param pointer to vector
 * @param an index
 * @param void pointer to a value
 * @ret   void
*/
void vec_insert(vector_t *vec, cuint64 idx, void *val, cuint64 size) {
    if (idx == vec->length)
        vec_append(vec, val, size);
    else if (idx > vec->length) {
        fprintf(stderr, "ERROR: insertion index out of range\n");
        exit(EXIT_FAILURE);
    }
    else {
        u_int64_t i;
        size_t new_vec_size = vec->length + 1;
        void **buff  = (void **) malloc(BYTES_OF_VOID(new_vec_size));
        vec->content = (void **) realloc(vec->content, BYTES_OF_VOID(new_vec_size));

        for (i = 0; i < idx; i++)
            buff[i] = vec_get(vec, i);

        buff[idx] = (void *) malloc(size);
        memcpy(buff[idx], val, size);

        for (i = idx; i < vec->length; i++)
            buff[i + 1] = vec_get(vec, i);

        for(i = 0; i < (u_int64_t) new_vec_size; i++)
            vec->content[i] = buff[i];

        vec_set(vec, idx, val, size);

        vec->length = new_vec_size;
        free(buff);
    }
}

#endif
