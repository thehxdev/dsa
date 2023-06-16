#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void) {
    vector_t ivec = vec_new(INT64_T);

    for (u_int64_t i = 0; i < 10; i++)
        vec_append(&ivec, (int64_t*)&i, sizeof(int64_t));

    int64_t x = 20;
    vec_insert(&ivec, 0, &x, sizeof(int64_t));

    vec_sort(&ivec, 0, ivec.length - 1);

    for (u_int64_t i = 0; i < ivec.length; i++)
        printf("%ld\n", *(int64_t *)vec_get(&ivec, i));

    vec_delete(&ivec);
    return EXIT_SUCCESS;
}
