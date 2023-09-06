#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void) {
    Vector *v = vec_new(JustPtr);
    char *str = to_str("Hello World!");

    vec_append(v, str, 0);
    printf("%s\n", VTOS(vec_get(v, 0)));

    vec_free(v, free);
    return EXIT_SUCCESS;
}

