#include <stdio.h>
#include "bubble.h"


int main(void) {
    int x[10] = {34, 76, 131, 1, -2, 4, 56, 12, 90, 8};
    bubble_sort(x, 10);

    printf("Arr = [ ");
    for (int i = 0; i < 10; i++)
        printf("%d ", x[i]);
    printf("]\n");

    return 0;
}
