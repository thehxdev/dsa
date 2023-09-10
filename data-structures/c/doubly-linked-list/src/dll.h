#ifndef DLL_H
#define DLL_H


#include <stddef.h>

typedef struct __node {
    int data;
    struct __node *next;
    struct __node *prev;
} Node;


typedef struct __dll {
    Node *head;
    Node *tail;
} DLL_t;


/**
 * Create a new node
 */
Node *node_new(int val);


/**
 * Create a new DLL
 */
DLL_t *dll_new();


/**
 * Add a new node to end of the DLL as TAIL
 */
int dll_append(DLL_t *dllp, int val);


/**
 * Add a new node to beginning of the DLL as HEAD
 */
int dll_prepend(DLL_t *dllp, int val);


/**
 * Find a node in DLL by it's index
 */
Node *dll_find_by_idx(DLL_t *dllp, size_t idx);


/**
 * Find a node in DLL by it's value
 */
Node *dll_find_by_val(DLL_t *dllp, int val);


/**
 * Find a node in DLL by it's value
 * (recursive implementation)
 */
Node *dll_find_by_val_Rec(Node *np, int val);


/**
 * Insert a new node after a specific Node in the DLL
 */
int dll_insert_after(DLL_t *dllp, Node *np, int val);


/**
 * delete a Node from DLL by it's value
 */
int dll_delete_by_val(DLL_t *dllp, int val);


/**
 * Delete a Node from DLL
 */
int dll_delete(DLL_t *dllp, Node *np);


/**
 * Free all nodes in a DLL with recursion
 */
void dll_free_nodes(Node *np);


/**
 * Free a doubly-linked-list from memory and 
 * it's nodes.
 */
void dll_free(DLL_t *dllp);


#endif // DLL_H
