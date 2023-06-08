#ifndef VECTOR_H
# define VECTOR_H

#ifndef vecTypeNum
# define vecTypeNum 0
#endif

/**
* 0 -> int64_t
* 1 -> char
* 2 -> char*
* _ -> int64_t
*/
#if vecTypeNum == 0
# define vecT int64_t
#elif vecTypeNum == 1
# define vecT char
#elif vecTypeNum == 2
# define vecT char*
#else
# define vecT int64_t
#endif

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>

# define cint64 const int64_t
# define cuint64 const u_int64_t

struct vector {
    size_t length;
    vecT *content;
};

typedef struct vector Vector;


Vector vecInit(void) {
    Vector vec;
    vec.content = NULL;
    vec.length = 0;

    return vec;
}


void vecAppend(Vector *vec, const vecT value) {
    if (vec->length > 0) {
        size_t newSize = sizeof(vecT) * (vec->length + 1);
        vec->content = (vecT *) realloc(vec->content, newSize);
    }
    else
        vec->content = (vecT *) malloc(sizeof(vecT));

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


void vecSet(Vector *vec, cuint64 index, const vecT value) {
    if (index < vec->length)
        vec->content[index] = value;
}


vecT vecAt(Vector *vec, cuint64 index) {
    if (index < vec->length)
        return vec->content[index];
    return -1;
}


#if (vecTypeNum == 0) || (vecTypeNum > 2)
int64_t vecSum(Vector *vec) {
    int64_t sum = 0;
    if (vec->length > 0) {
        for (int i = 0; i < (int) vec->length; i++)
            sum += vecAt(vec, i);
    }
    return sum;
}
#endif


void vecPrint(Vector *vec) {
    if (vec->length > 0) {
        printf("vec = { ");
        for (u_int64_t i = 0; i < (u_int64_t) vec->length; i++) {
#if vecTypeNum == 0
            printf("%ld, ", vecAt(vec, i));
#elif vecTypeNum == 1
            printf("%c, ", vecAt(vec, i));
#elif vecTypeNum == 2
            printf("%s, ", vecAt(vec, i));
#else
            printf("%ld, ", vecAt(vec, i));
#endif
        }
        printf("}\n");
        fflush(stdout);
    }
}


void vecReverse(Vector *vec) {
    vecT *buffer = (vecT *) malloc(sizeof(vecT) * vec->length);
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


vecT vecPop(Vector *vec) {
    int64_t last_element = -1;
    if (vec->length > 0) {
        size_t last_element_index = vec->length - 1;
        last_element = vec->content[last_element_index];
        vec->content[last_element_index] = 0;
        vec->content = (vecT *) realloc(vec->content, (sizeof(vecT) * (vec->length - 1)));
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


#if (vecTypeNum < 2) || (vecTypeNum > 2)
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


void vecSort(Vector *vec, cuint64 lower, cuint64 upper) {
    // quicksort
    if (upper > lower) {
        int64_t partitionIndex = partition(vec, lower, upper);

        vecSort(vec, lower, partitionIndex - 1);
        vecSort(vec, partitionIndex + 1, upper);
    }
}
#endif


void vecClean(Vector *vec) {
    vecDel(vec);
    vec->content = NULL;
    vec->length = 0;
}


void vecCpy(Vector *vec1, Vector *vec2) {
    if (vec2->length > 0) {
        if (vec1->content)
            vecClean(vec1);
        vec1->content = (vecT *) malloc(sizeof(vecT) * vec2->length);

        for (int64_t i = 0; i < (int64_t)vec2->length; i++) {
            vecSet(vec1, i, vecAt(vec2, i));
        }
    }
}


void vecInsert(Vector *vec, cuint64 index, const vecT value) {
    if (index == vec->length)
        vecAppend(vec, value);
    else if (index > vec->length) {
        fprintf(stderr, "ERROR: insertion index out of range\n");
        exit(EXIT_FAILURE);
    }
    else {
        u_int64_t i;
        size_t new_vec_size = vec->length + 1;
        vecT *buff = (vecT *) malloc(new_vec_size * sizeof(vecT));
        vec->content = (vecT *) realloc(vec->content, new_vec_size * sizeof(vecT));

        for (i = 0; i < index; i++)
            buff[i] = vecAt(vec, i);

        buff[index] = value;

        for (i = index; i < (u_int64_t) vec->length; i++)
            buff[i + 1] = vecAt(vec, i);

        for(i = 0; i < (u_int64_t) new_vec_size; i++)
            vec->content[i] = buff[i];

        vec->length = new_vec_size;
        free(buff);
    }
}

#endif
