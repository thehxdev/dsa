#include "bubble.h"

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}


void bubble_sort(int *arr, size_t len) {
    int i, j;
    for (i = len - 1; i > 0; i--)
        for (j = 0; j < i; j++)
            if (arr[j] > arr[j+1])
                swap(&arr[j], &arr[j+1]);
}
