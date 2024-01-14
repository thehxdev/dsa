#include <stdio.h>
#include <assert.h>
#include "b-search.h"

#define ARR_LEN 10

int main(void) {
    int arr[ARR_LEN] = { 54, 12, 1, 23, 100, 121, 5563, 98, 4, 212 };

    bubble_sort(arr, ARR_LEN);

    int *x = binary_search(arr, ARR_LEN, 100);
    assert(*x == 100);

    int *y = binary_search(arr, ARR_LEN, 19831);
    assert(y == NULL);

    printf("All tests are PASSED!\n");
}
