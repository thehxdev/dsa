#include <stdio.h>
#include "dll.h"

int main(void) {
    // Create a new doubly-linked-list
    DLL_t *dll = dll_new();
    int x = 69, y = 75, z = 85;

    // add some data
    dll_append(dll, &x, sizeof(x));
    dll_append(dll, &y, sizeof(y));
    dll_append(dll, &z, sizeof(z));

    // prepend z as head of DLL
    dll_prepend(dll, &z, sizeof(z));


    // add numbers from 100 to 110 to DLL
    for (int i = 100; i < 110; i++)
        dll_append(dll, &i, sizeof(i));

    /*
     * delete a node from DLL by it's value
     *
     * if value does not exist in DLL, `dll_deleteByVal`
     * function will skip deleting.
     */
    int s = 100; // s -> sample number
    dll_deleteByVal(dll, &s, sizeof(s));

    /*
     * delete a node from DLL by it's index
     *
     * if index is out of range, `dll_deleteByIdx`
     * function will skip deleting.
     */
    dll_deleteByIdx(dll, 0);

    /*
     * index out of range so function returns 1
     * as return code and skips deleting
     */
    dll_deleteByIdx(dll, 100);


    // find a node in DLL by it's value
    s = 103;
    Node *n = dll_findNodeByVal(dll, &s, sizeof(s)); // n -> sample node
    if (n == NULL)
        goto ret;

    /*
     * delete a node from DLL by it's address
     * 
     * if given node is NULL function will skip deleting
     */
    dll_deleteByAddr(dll, n);


    /*
     * insert a new value (node) to a specific index
     * of DLL.
     * here we add number 590 at index 0 (as head of DLL)
     */
    s = 590;
    dll_insertAtIdx(dll, 0, &s, sizeof(s));


    // find a node by it's index in DLL
    n = dll_findNodeByIdx(dll, 0);
    if (n == NULL)
        goto ret;

    /*
     * insert a new value (node) to a specific index
     * of DLL.
     * here we add number 23 after node n that found above by it's index
     */
    s = 23;
    dll_insertAfterNode(dll, n, &s, sizeof(s));

    // print all values in DLL
    Node *tmp = dll->head;
    while (tmp != NULL) {
        printf("%d\n", *(int*)tmp->data);
        tmp = tmp->next;
    }

ret:
    dll_free(dll);
    return 0;
}

