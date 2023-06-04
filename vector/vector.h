#ifndef VECTOR_H
# define VECTOR_H

# include <sys/types.h>
# include <stdbool.h>

# define cint64 const int64_t
# define cuint64 const u_int64_t

struct vector {
    size_t length;
    int64_t *content;
};

typedef struct vector Vector;


Vector vecInit(void);
void vecAppend(Vector *vec, cint64 value);
void vecSwap(Vector *vec, cuint64 index1, cuint64 index2);
void vecDel(Vector *vec);
void vecSet(Vector *vec, cuint64 index, cint64 value);
int64_t vecAt(Vector *vec, cuint64 index);
int64_t vecSum(Vector *vec);
void vecPrint(Vector *vec);
void vecReverse(Vector *vec);
int64_t vecPop(Vector *vec);
size_t vecSize(Vector *vec);
bool vecIsEmpty(Vector *vec);
int64_t vecFind(Vector *vec, cint64 value);
int64_t vecBegin(Vector *vec);
int64_t vecEnd(Vector *vec);
void vecSort(Vector *vec, int64_t lower, int64_t upper);
void vecClean(Vector *vec);
void vecCpy(Vector *vec1, Vector *vec2);


#endif
