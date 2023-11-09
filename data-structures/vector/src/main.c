#include <stdio.h>
#include <stdlib.h>
#include "vector.h"


int main(void) {
    // Create a new vector
    Vector *v = vec_new(20);

    // Add numbers 0 to 20 to vector
    for (int i = 0; i < 30; i++)
        vec_append(v, i);

    vec_print(v);
    vec_free(v);
    return EXIT_SUCCESS;
}

