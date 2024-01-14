#include <stdio.h>
#include <assert.h>
#include "l-search.h"

#define ARR_LEN 10

int main(void) {
    int arr[ARR_LEN] = { 1, 21, 4, 34, 76, 93, 13, 67, 99, 100 };

    int *x = linear_search(arr, ARR_LEN, 76);
    assert(*x == 76);

    int *y = linear_search(arr, ARR_LEN, 0);
    assert(y == NULL);

    printf("All Tests Are PASSED!\n");
}
