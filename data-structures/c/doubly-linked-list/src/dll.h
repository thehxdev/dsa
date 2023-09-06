#ifndef DLL_H
#define DLL_H


#include <stddef.h>

typedef struct __node {
    void *data;
    size_t size;
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
Node *node_new(void *val, size_t size);


/**
 * Free a node's space from memory
 */
void node_free(Node *np);


/**
 * Create a new DLL
 */
DLL_t *dll_new();


/**
 * Add a new node to end of the DLL as TAIL
 */
int dll_append(DLL_t *dllp, void *val, size_t size);


/**
 * Add a new node to beginning of the DLL as HEAD
 */
int dll_prepend(DLL_t *dllp, void *val, size_t size);


/**
 * Find a node in DLL by it's index
 */
Node *dll_findNodeByIdx(DLL_t *dllp, size_t idx);


/**
 * Find a node in DLL by it's value
 */
Node *dll_findNodeByVal(DLL_t *dllp, void *val, size_t size);


/**
 * Find a node in DLL by it's value
 * (recursive implementation)
 */
Node *dll_findNodeByVal_Rec(Node *np, void *val, size_t size);


/**
 * Insert a new node to DLL with a specific index
 */
int dll_insertAtIdx(DLL_t *dllp, size_t idx, void *val, size_t size);


/**
 * Insert a new node after a specific Node in the DLL
 */
int dll_insertAfterNode(DLL_t *dllp, Node *np, void *val, size_t size);


/**
 * delete a value from DLL by it's value
 */
int dll_deleteByVal(DLL_t *dllp, void *val, size_t size);


/**
 * Delete a node from DLL by it's index
 */
int dll_deleteByIdx(DLL_t *dllp, size_t idx);


/**
 * Delete a node from DLL by it's memory address
 */
int dll_deleteByAddr(DLL_t *dllp, Node *np);


/**
 * Free a doubly-linked-list from memory and 
 * it's nodes.
 */
void dll_free(DLL_t *dllp);


#endif // DLL_H
