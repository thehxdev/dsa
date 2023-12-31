#include <stdio.h>
#include "ll.h"


int main(void) {
    // Initialize a new singly-linked-list
    LL_t *ll = ll_new();

    int x = 75, y = 69, t = 85, z = 95;
    // prepend value of x (as head)
    ll_prepend(ll, x);

    for (int i = 1; i <= 10; i++)
        /*
         * append numbers form 1 to 10
         * `ll_append` adds a new value
         * at end of the LL (as tail)
         */ 
        ll_append(ll, i);

    /*
     * insert some values manualy to 
     * a specific index
     */
    ll_insert_at_idx(ll, 0, y);
    ll_insert_at_idx(ll, 2, z);
    ll_insert_at_idx(ll, 7, t);

    /*
     * if insertion index is out of range
     * ll_insertAtIdx function will skip inserting
     * to prevent segfault and NULL pointer derefrence
     * and returns 1 as error code
     */
    int err = ll_insert_at_idx(ll, 14, x);
    printf("Error Code: %d - Instertoin index out of range - skip inserting\n", err);


    /*
     * delete a value from LL by it's index in LL
     */
    ll_delete_by_idx(ll, 0);
    ll_delete_by_idx(ll, 1);
    ll_delete_by_idx(ll, 11);
    ll_delete_by_idx(ll, 6);

    /*
     * for deleting from LL, if index is out of range,
     * ll_delete function will skip to prevent segfault
     * and NULL pointer derefrence.
     */
    err = ll_delete_by_val(ll, 13);
    printf("Error Code: %d - Deletetion index out of range - skip deleting\n\n", err);

    /*
     * delete a value from LL by it's value
     * 
     * ll_deleteByVal uses `memcmp` function so
     * you can pass it whatever value you want
     *
     * skip deleting if value pointer is NULL
     * or value not found in LL
     */
    ll_delete_by_val(ll, z);

    Node *tmp = ll->head;
    while (tmp != NULL) {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }

    ll_free(ll->head);
    return 0;
}

