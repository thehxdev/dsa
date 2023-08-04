#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vector.h"


int main(void) {
    Vector *vec  = vec_new();
    Vector *nums = vec_new();

    char *str1 = "Hello From C!";
    char *str2 = "Another Statement.";
    char *str3 = "OOP Sucks!";
    
    // include null terminator character in `size` (last) argument
    // for vec_append
    vec_append(vec, str1, strlen(str1) + 1);
    vec_append(vec, str2, strlen(str2) + 1);

    // change str1 to str3 in vector
    vec_change(vec, 0, str3, strlen(str3) + 1);

    int x = 5, y = 10, z = 20;
    vec_append(nums, &x, sizeof(x));
    vec_append(nums, &y, sizeof(y));
    vec_append(nums, &z, sizeof(z));


    for (uint32_t i = 0; i < nums->len; i++)
        printf("%d\n", VTOI(vec_getData(nums, i)));

    for (uint32_t j = 0; j < vec->len; j++)
        printf("%s\n", VTOS(vec_getData(vec, j)));


    vec_free(vec);
    vec_free(nums);
    return EXIT_SUCCESS;
}

