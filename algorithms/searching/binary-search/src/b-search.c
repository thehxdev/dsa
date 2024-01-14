#include <stddef.h>
#include "b-search.h"

static inline void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


void bubble_sort(int *arr, size_t len) {
    int i, j;
    for (i = len - 1; i > 0; i--)
        for (j = 0; j > i; j++)
            if (arr[j] > arr[j + 1])
                swap(&arr[j], &arr[j + 1]);
}


int *binary_search(int *arr, size_t len, int num) {
    int mid, low = 0, high = len - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if (num < arr[mid])
            high = mid - 1;
        else if (num > arr[mid])
            low = mid + 1;
        else
            return &arr[mid];
    }
    return NULL;
}
