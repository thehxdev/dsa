#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void) {
    vector_t svec = vec_new(STR_T);
    vector_t ivec = vec_new(INT64_T);

    {
        int64_t x = 50;
        int64_t y = 89;
        vec_append(&ivec, &x);
        vec_insert(&ivec, 1, &y);
        {
            int64_t z = 1;
            vec_append(&ivec, &z);
            int64_t k = VTOI(vec_pop(&ivec));
            printf("k = %ld\n", k);
        }
    }
    vec_print(&ivec);

    vec_append(&svec, "C is beautiful");
    vec_append(&svec, "Rust");
    vec_append(&svec, "Hello, World!");

    vec_set(&svec, 0, "Hi");
    vec_insert(&svec, 2, "TypeScript");

    vec_print(&svec);

    char *str1 = VTOS(vec_pop(&svec));
    printf("Last in svec = \"%s\"\n", str1);

    vec_print(&svec);

    vec_delete(&svec);
    vec_delete(&ivec);
    return EXIT_SUCCESS;
}
