#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>

#define cuint64 const u_int64_t
#define BYTES_OF_VECT(bytes) (sizeof(vecT) * (bytes))
#define CHECK_IDX(vecptr, idx) ((idx) < (vecptr->length) || (idx) == 0)

/**
 * if vecTnum is not defined,
 * set vector's default type to int64_t (0).
 */
#ifndef vecTnum
# define vecTnum 0
#endif

/*
 * check if number of vector type is valid
 * (if it's already defined)
 */
#if (vecTnum < 0) || (vecTnum > 2)
# undef vecTnum
# define vecTnum 0
#endif

/*
 * 0 -> int64_t (default)
 * 1 -> char
 * 2 -> char * (string)
 */
#if vecTnum == 0
# define vecT int64_t
#elif vecTnum == 1
# define vecT char
#elif vecTnum == 2
# define vecT char*
#endif

struct __vector {
    u_int64_t length;
    vecT *content;
};

typedef struct __vector vector_t;


/**
 * Create a new vector
 *
 * @ret a vector type instance
 */
vector_t vec_new(void) {
    vector_t vec;
    vec.content = NULL;
    vec.length  = 0;

    return vec;
}


/**
 * append an item with type vecT to the end of vector
 * 
 * @param pointer to a vector
 * @param A value to append with type vecT
 * @ret   void
 */
void vec_append(vector_t *vec, vecT val) {
    if (vec->content) {
        u_int64_t new_size = (vec->length + 1);
        vec->content = (vecT *) realloc(vec->content, BYTES_OF_VECT(new_size));
    }
    else
        vec->content = (vecT *) malloc(BYTES_OF_VECT(1));

    u_int64_t last_index = vec->length;

#if vecTnum == 2
    u_int64_t str_size = strlen(val);
    vec->content[last_index] = (vecT) malloc(str_size);
    strcpy(vec->content[last_index], val);
#else
    vec->content[last_index] = val;
#endif

    vec->length++;
}


/**
 * get an index's value in the vector
 *
 * @param pointer to a vector
 * @param an index
 * @ret   a value with type vecT
 */
vecT vec_get(vector_t *vec, cuint64 idx) {
    if (CHECK_IDX(vec, idx))
        return vec->content[idx];
    fprintf(stderr, "ERROR: cannot get value (index %ld out of range)\n", idx);
    exit(1);
}


/**
 * free up a vector's content
 *
 * @param pointer to a vector
 * @ret   void
 */
void vec_delete(vector_t *vec) {
    if (vec->content) {
#if vecTnum == 2
        for (u_int64_t i = 0; i < vec->length; i++)
            free(vec_get(vec, i));
#endif
        free(vec->content);
    }
}


/**
 * clean up a vector and make it empty
 *
 * @param pointer to a vector
 */
void vec_clean(vector_t *vec) {
    vec_delete(vec);
    vec->content = NULL;
    vec->length  = 0;
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
#if vecTnum == 2
        u_int64_t str1_size = strlen(vec->content[idx1]);
        u_int64_t str2_size = strlen(vec->content[idx2]);

        vecT tmpval1 = (vecT) malloc(BYTES_OF_VECT(str1_size));
        vecT tmpval2 = (vecT) malloc(BYTES_OF_VECT(str2_size));

        strcpy(tmpval1, vec->content[idx1]);
        strcpy(tmpval2, vec->content[idx2]);

        vec->content[idx1] = (vecT) realloc(vec->content[idx1], str2_size);
        vec->content[idx2] = (vecT) realloc(vec->content[idx2], str1_size);

        strcpy(vec->content[idx1], tmpval2);
        strcpy(vec->content[idx2], tmpval1);
#else
        vecT tmpval = vec->content[idx1];
        vec->content[idx1] = vec->content[idx2];
        vec->content[idx2] = tmpval;
#endif
    }
}


/**
 * print a vector
 *
 * @param pointer to a vector
 */
void vec_print(vector_t *vec) {
    if (vec->length > 0) {
        printf("{ ");
        u_int64_t i;
        for (i = 0; i < vec->length; i++)
#if vecTnum == 0
            printf("%ld, ", vec_get(vec, i));
#elif vecTnum == 1
            printf("%c, ", vec_get(vec, i));
#elif vecTnum == 2
            printf("\"%s\", ", vec_get(vec, i));
#endif
        printf("}\n");
        fflush(stdout);
    }
}


#if vecTnum != 2
/**
 * if vecT is not (char*) return sum of
 * all the values in the vector
 *
 * @param pointer to a vector
 * @ret   an int64
 */
int64_t vec_sum(vector_t *vec) {
    int64_t sum = 0;
    for (u_int64_t i = 0; i < vec->length; i++)
        sum += vec_get(vec, i);
    return sum;
}
#endif


/**
 * change a vector's index to a new value
 *
 * @param pointer to a vector
 * @param an index
 * @param a value
 * @ret   void
 */
void vec_set(vector_t *vec, cuint64 idx, vecT val) {
    if (CHECK_IDX(vec, idx)) {
#if vecTnum == 2
        u_int64_t val_len = strlen(val);

        if (vec->content[idx]) {
            vec->content[idx] = (vecT) realloc(vec->content[idx], val_len);
        }
        else {
            vec->content[idx] = (vecT) malloc(val_len);
        }

        strcpy(vec->content[idx], val);
#else
        vec->content[idx] = val;
#endif
    }
}


/**
 * reverse a vector
 *
 * @param pointer to a vector
 * @ret   void
 */
void vec_reverse(vector_t *vec) {
    vecT *buffer = (vecT *) malloc(BYTES_OF_VECT(vec->length));
    u_int64_t j = 0;

    for (int64_t i = (vec->length - 1); i >= 0; i--) {
#if vecTnum == 2
        vecT current_val = vec_get(vec, i);
        u_int64_t str_size = strlen(current_val);
        buffer[j] = (vecT) malloc(str_size);
        strcpy(buffer[j], current_val);
        j++;
#else
        buffer[j] = vec_get(vec, i);
        j++;
#endif
    }

    for (u_int64_t i = 0; i < vec->length; i++) {
        vec_set(vec, i, buffer[i]);
    }

    free(buffer);
}


/**
 * search for a value in vector
 *
 * @param pointer to a vector
 * @param value that you are searching for
 * @ret   index of the value (-1 if not found)
*/
int64_t vec_find(vector_t *vec, vecT val) {
    for (u_int64_t i = 0; i < vec->length; i++) {
#if vecTnum == 2
        if (strcmp(vec_get(vec, i), val) == 0)
            return i;
#else
        if (vec_get(vec, i) == val)
            return i;
#endif
    }
    return -1;
}

#if vecTnum != 2
// partition function for vec_sort (quicksort)
static int64_t partition(vector_t *vec, int64_t lower, int64_t upper) {
    int64_t i = (lower - 1);
    const int64_t pivot = vec_get(vec, upper);

    for (int64_t j = lower; j < upper; j++) {
        if (vec_get(vec, j) <= pivot) {
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
#endif


/**
 * copy src vector to dest
 * WARN: this function wipes dest vector!
 *
 * @param pointer to vector dest
 * @param pointer to vector src
 * @ret   void
*/
void vec_cpy(vector_t *dest, vector_t *src) {
    if (src->length > 0) {
        if (dest->content)
            vec_clean(dest);
        dest->content = (vecT *) malloc(BYTES_OF_VECT(src->length));

        dest->length = src->length;
        for (u_int64_t i = 0; i < src->length; i++)
            vec_set(dest, i, vec_get(src, i));
    }
}


/**
 * insert to a specific index in vector
 *
 * @param pointer to vector
 * @param an index
 * @param a value
 * @ret   void
*/
// TODO: implement for char* too
#if vecTnum != 2
void vec_insert(vector_t *vec, cuint64 idx, vecT val) {
    if (idx == vec->length)
        vec_append(vec, val);
    else if (idx > vec->length) {
        fprintf(stderr, "ERROR: insertion index out of range\n");
        exit(EXIT_FAILURE);
    }
    else {
        u_int64_t i;
        size_t new_vec_size = vec->length + 1;
        vecT *buff = (vecT *) malloc(new_vec_size * sizeof(vecT));
        vec->content = (vecT *) realloc(vec->content, new_vec_size * sizeof(vecT));

        for (i = 0; i < idx; i++)
            buff[i] = vec_get(vec, i);

        buff[idx] = val;

        for (i = idx; i < vec->length; i++)
            buff[i + 1] = vec_get(vec, i);

        for(i = 0; i < (u_int64_t) new_vec_size; i++)
            vec->content[i] = buff[i];

        vec->length = new_vec_size;
        free(buff);
    }
}
#endif

#endif
