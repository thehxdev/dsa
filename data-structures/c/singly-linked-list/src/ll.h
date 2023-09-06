#ifndef LL_H
#define LL_H


#include <stddef.h>

typedef struct __node {
    void *data;
    size_t size;
    struct __node *next;
} Node;


typedef struct __ll {
    Node *head;
    Node *tail;
} LL_t;


/**
 * Create a new node
 */
Node *node_new(void *val, size_t size);


/**
 * Free a node's space from memory
 */
void node_free(Node *np);


/**
 * Create a new LL
 */
LL_t *ll_new();


/**
 * Add a new node to end of the LL as TAIL
 */
int ll_append(LL_t *llp, void *val, size_t size);


/**
 * Add a new node to beginning of the LL as HEAD
 */
int ll_prepend(LL_t *llp, void *val, size_t size);


/**
 * Find a node in LL by it's index
 */
Node *ll_findNodeByIdx(LL_t *llp, size_t idx);


/**
 * Find a node in LL by it's value
 * (Recursive implementation)
 */
Node *ll_findNodeByVal_Rec(Node *np, void *val, size_t size);


/**
 * Find a node in LL by it's value
 */
Node *ll_findNodeByVal(LL_t *llp, void *val, size_t size);


/**
 * Insert a new node to LL with a specific index
 */
int ll_insertAtIdx(LL_t *llp, size_t idx, void *val, size_t size);


/**
 * Insert a new node after a specific Node in the LL
 */
int ll_insertAfterNode(LL_t *llp, Node *np, void *val, size_t size);


/**
 * delete a value from LL by it's value
 */
int ll_deleteByVal(LL_t *llp, void *val, size_t size);


/**
 * Delete a node from LL by it's index
 */
int ll_deleteByIdx(LL_t *llp, size_t idx);


/**
 * Free a singly-linked-list from memory and 
 * it's nodes.
 */
void ll_free(LL_t *llp);

#endif // LL_H

