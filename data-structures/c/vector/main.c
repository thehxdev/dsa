#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "vector.h"


int main(void) {
    Vector *strs  = vec_new();
    Vector *nums = vec_new();
    Vector *arrs = vec_new();

    char *str1 = "Hello From C!";
    char *str2 = "Another Statement.";
    char *str3 = "OOP Sucks!";
    
    // include null terminator character in `size` (last) argument
    // for vec_append
    vec_append(strs, str1, strlen(str1) + 1);
    vec_append(strs, str2, strlen(str2) + 1);

    // change str1 to str3 in vector
    vec_change(strs, 0, str3, strlen(str3) + 1);

    // append to nums vector from an array
    int arr[6] = {5, 10, 20, 69, 75, 85};
    for (uint32_t i = 0; i < 6; i++)
        vec_append(nums, &arr[i], sizeof(int));

    // store an array to vector (arrs)
    vec_append(arrs, arr, sizeof(arr));

    // get array stored in arrs vector
    // beware to cast types correctly
    int *pArr = (int*) vec_getData(arrs, 0);
    // print array's content
    printf("Content of pArr in arrs vector:\n");
    for (uint32_t i = 0; i < 6; i++)
        printf("%d\n", pArr[i]);

    printf("===============================\n");

    printf("Content of nums vector:\n");
    for (uint32_t i = 0; i < nums->len; i++)
        printf("%d\n", VTOI(vec_getData(nums, i)));

    printf("===============================\n");

    printf("Content of strs vector:\n");
    for (uint32_t j = 0; j < strs->len; j++)
        printf("%s\n", VTOS(vec_getData(strs, j)));


    vec_free(strs);
    vec_free(nums);
    vec_free(arrs);
    return EXIT_SUCCESS;
}

