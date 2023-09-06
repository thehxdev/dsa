#include <stdio.h>
#include <stdlib.h>
#include "stacka.h"

#define ARR_LEN 6

int main(void) {
    Stack *s = stk_new();
    int arr[ARR_LEN] = {69, 75, 85, 50, 23, 96};

    for (int i = 0; i < ARR_LEN; i++)
        stk_push(s, &arr[i], sizeof(int));

    // remove last element and delete it from memory
    stk_popD(s);

    // remove last element and return it
    int *x = (int*) stk_pop(s);
    printf("Removed element: %d\n\n", *x);

    for (int j = 0; j < (int)s->len; j++)
        printf("%d\n", *(int*)s->elems[j]);

    free(x);
    stk_free(s);
    return 0;
}
