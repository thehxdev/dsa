#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "array.h"


int main(void) {
    srand(time(NULL));

    size_t i;
    List *nums = list_new(20, xfree);
    for (size_t i = 0; i < 20; i++)
        list_append(nums, &i, sizeof(i));

    printf("Initial List = [ ");
    for (i = 0; i < nums->len; i++)
        printf("%d ", *(int*)nums->vals[i]);
    printf("]\n\n");

    // Just print the inner lists and free them
    // while printing them.
    // I don't use `list_free` function on sub-lists
    // because when calling `list_free` on `breaked` list
    // at the end of the program, we encounter a double-free error.
    List *breaked = list_breakdown_rand(nums, 5);
    for (i = 0; i < breaked->len; i++) {
        List *tmp = (List*)breaked->vals[i];
        printf("chunk %lu -> [ ", i);
        for (size_t j = 0; j < tmp->len; j++)
            printf("%d ", *(int*)tmp->vals[j]);
        printf("]\n");
    }

    List *merged = list_merge_inner(breaked);
    printf("\nMerged = [ ");
    for (i = 0; i < merged->len; i++) {
        printf("%d ", *(int*)merged->vals[i]);
    }
    printf("]\n");

    list_free(breaked);
    list_free(merged);
    list_free(nums);
    return 0;
}
