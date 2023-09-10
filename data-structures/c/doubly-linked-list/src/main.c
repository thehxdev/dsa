#include <stdio.h>
#include "dll.h"

int main(void) {
    // Create a new doubly-linked-list
    DLL_t *dll = dll_new();
    int x = 69, y = 75, z = 85;

    // add some data
    dll_append(dll, x);
    dll_append(dll, y);
    dll_append(dll, z);

    // prepend z as head of DLL
    dll_prepend(dll, z);


    // add numbers from 100 to 110 to DLL
    for (int i = 100; i < 110; i++)
        dll_append(dll, i);

    /*
     * delete a node from DLL by it's value
     *
     * if value does not exist in DLL, `dll_deleteByVal`
     * function will skip deleting.
     */
    int s = 100; // s -> sample number
    dll_delete_by_val(dll, s);


    // find a node in DLL by it's value
    s = 103;
    Node *n = dll_find_by_val(dll, s); // n -> sample node
    if (n == NULL) {
        dll_free(dll);
        return 1;
    }

    /*
     * delete a node from DLL by it's address
     * 
     * if given node is NULL function will skip deleting
     */
    dll_delete(dll, n);


    // find a node by it's index in DLL
    n = dll_find_by_idx(dll, 0);
    if (n == NULL) {
        dll_free(dll);
        return 1;
    }

    /*
     * insert a new value (node) to a specific index
     * of DLL.
     * here we add number 23 after node n that found above by it's index
     */
    s = 23;
    dll_insert_after(dll, n, s);

    // print all values in DLL
    Node *tmp = dll->head;
    while (tmp != NULL) {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }

    dll_free(dll);
    return 0;
}
