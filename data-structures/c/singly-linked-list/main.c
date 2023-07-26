#include <stdio.h>
#include "ll.h"


int main(void) {
    // Initialize a new singly-linked-list
    LL_t *ll = ll_new();

    int x = 75, y = 69, t = 85, z = 95;
    // prepend value of x (as head)
    ll_prepend(ll, &x, sizeof(x));

    for (int i = 1; i <= 10; i++)
        // append numbers form 1 to 10
        ll_append(ll, &i, sizeof(i));

    /*
     * insert some values manualy to 
     * a specific index
     */
    ll_insert(ll, 0, &y, sizeof(x));
    ll_insert(ll, 2, &z, sizeof(z));
    ll_insert(ll, 7, &t, sizeof(x));

    /*
     * if insertion index is out of range
     * ll_insert functoin will skip inserting
     * to prevent segfault and NULL pointer derefrence
     * and returns 1 as error code
     */
    int err = ll_insert(ll, 14, &x, sizeof(x));
    printf("Error Code: %d - Instertoin index out of range - skip inserting\n\n", err);

    Node *tmp = ll->head;
    while (tmp != NULL) {
        printf("%d\n", *(int*)tmp->data);
        tmp = tmp->next;
    }

    ll_free(ll);
    return 0;
}
