#include <stdio.h>
#include <stdlib.h>
#include "stackll.h"


int main(void) {
    Stack *s = stk_new();

    for (int i = 0; i < 10; i++)
        stk_push(s, i);

    Node *n = stk_pop(s);
    // removed number 9 from stack
    printf("Removed node data: %d\n", n->data);

    // Remove and Free last node from stack (number 8)
    stk_popD(s);
    printf("Removed number 8 with stk_popD function!\n\n");

    printf("Stack's Data:\n");
    Node *tmp = s->top;
    while (tmp != NULL) {
        printf("%d\n", tmp->data);
        tmp = tmp->prev;
    }

    free(n);
    stk_free(s);
    return 0;
}

