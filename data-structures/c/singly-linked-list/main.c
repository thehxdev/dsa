#include <stdio.h>
#include "ll.h"


int main(void) {
    LL_t *ll = ll_new();

    int x = 999;
    ll_prepend(ll, &x, sizeof(x));

    for (int i = 1; i <= 10; i++)
        ll_append(ll, &i, sizeof(i));

    Node *tmp = ll->head;
    while (tmp != NULL) {
        printf("%d\n", *(int*)tmp->data);
        tmp = tmp->next;
    }

    ll_free(ll);
    return 0;
}
