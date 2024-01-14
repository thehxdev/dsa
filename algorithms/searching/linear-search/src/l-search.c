#include <stddef.h>
#include "l-search.h"

int *linear_search(int *arr, size_t len, int num) {
    for (size_t i = 0; i < len; i++)
        if (arr[i] == num)
            return &arr[i];
    return NULL;
}
