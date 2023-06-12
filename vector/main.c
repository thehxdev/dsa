#include <stdio.h>
#include <stdlib.h>

#define vecTnum 2
#include "vector.h"

int main(void) {
    vector_t vec = vec_new();

    vec_append(&vec, "C is beautiful");
    vec_append(&vec, "Rust");
    vec_append(&vec, "Hello, World!");

    vec_print(&vec);
    vec_delete(&vec);
    return EXIT_SUCCESS;
}
