#ifndef _STDIO_H
# include <stdio.h>
#endif

#include <stdlib.h>

#include "vector.h"


Vector vecInit(void) {
    Vector vec;
    vec.content = NULL;
    vec.length = 0;

    return vec;
}


void vecAppend(Vector *vec, cint64 value) {
    if (vec->length > 0)
        vec->content = (int64_t *) realloc(vec->content, (sizeof(int64_t) * (vec->length + 1)));
    else
        vec->content = (int64_t *) malloc(sizeof(int64_t));

    vec->content[vec->length] = value;
    vec->length++;
}


void vecSwap(Vector *vec, cuint64 index1, cuint64 index2) {
    if ( index1 < vec->length && index2 < vec->length ) {
        cint64 num1 = vec->content[index1];
        vec->content[index1] = vec->content[index2];
        vec->content[index2] = num1;
    }
}


void vecDel(Vector *vec) {
    if (vec->content)
        free(vec->content);
}


void vecSet(Vector *vec, cuint64 index, cint64 value) {
    if (index < vec->length)
        vec->content[index] = value;
}


int64_t vecAt(Vector *vec, cuint64 index) {
    if (index < vec->length)
        return vec->content[index];
    return -1;
}


int64_t vecSum(Vector *vec) {
    int64_t sum = 0;
    if (vec->length > 0) {
        for (int i = 0; i < (int) vec->length; i++)
            sum += vecAt(vec, i);
    }
    return sum;
}


void vecPrint(Vector *vec) {
    if (vec->length > 0) {
        printf("vec = { ");
        for (int i = 0; i < (int) vec->length; i++) {
            printf("%ld, ", vecAt(vec, i));
        }
        printf("}\n");
        fflush(stdout);
    }
}


void vecReverse(Vector *vec) {
    int64_t *buffer = (int64_t *) malloc(sizeof(int64_t) * vec->length);
    u_int64_t j = 0;

    for (int64_t i = (int64_t)vec->length - 1; i >= 0; i--) {
        buffer[j] = vecAt(vec, i);
        j++;
    }
    
    for (int64_t i = 0; i < (int64_t)vec->length; i++) {
        vecSet(vec, i, buffer[i]);
    }

    free(buffer);
}


int64_t vecPop(Vector *vec) {
    int64_t last_element = -1;
    if (vec->length > 0) {
        size_t last_element_index = vec->length - 1;
        last_element = vec->content[last_element_index];
        vec->content[last_element_index] = 0;
        vec->content = (int64_t *) realloc(vec->content, (sizeof(int64_t) * (vec->length - 1)));
        vec->length--;
    }
    return last_element;
}


size_t vecSize(Vector *vec) {
    return vec->length;
}


bool vecIsEmpty(Vector *vec) {
    return (vec->length > 0) ? true : false;
}


int64_t vecFind(Vector *vec, cint64 value) {
    for (int64_t i = 0; i < (int64_t)vec->length; i++) {
        if (vecAt(vec, i) == value)
            return i;
    }
    return -1;
}


int64_t vecBegin(Vector *vec) {
    if (vec->length > 0)
        return 0;
    return -1;
}


int64_t vecEnd(Vector *vec) {
    if (vec->length > 0)
        return (int64_t) (vec->length - 1);
    return -1;
}


// partition function for vecSrot (quicksort)
static int64_t partition(Vector *vec, int64_t lower, int64_t upper) {
    int64_t i = (lower - 1);
    const int64_t pivot = vecAt(vec, upper);

    for (int64_t j = lower; j < upper; j++) {
        if (vecAt(vec, j) <= pivot) {
            i++;
            vecSwap(vec, i, j);
        }
    }

    vecSwap(vec, i + 1, upper);
    return (i + 1);
}


void vecSort(Vector *vec, int64_t lower, int64_t upper) {
    // quicksort
    if (upper > lower) {
        int64_t partitionIndex = partition(vec, lower, upper);

        vecSort(vec, lower, partitionIndex - 1);
        vecSort(vec, partitionIndex + 1, upper);
    }
}


void vecClean(Vector *vec) {
    vecDel(vec);
    vec->content = NULL;
    vec->length = 0;
}


void vecCpy(Vector *vec1, Vector *vec2) {
    if (vec2->length > 0) {
        if (vec1->content)
            vecClean(vec1);
        vec1->content = (int64_t *) malloc(sizeof(int64_t) * vec2->length);

        for (int64_t i = 0; i < (int64_t)vec2->length; i++) {
            vecSet(vec1, i, vecAt(vec2, i));
        }
    }
}

