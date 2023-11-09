#ifndef LL_H
#define LL_H


#include <stddef.h>

typedef struct __node {
    int data;
    struct __node *next;
} Node;


typedef struct __ll {
    Node *head;
    Node *tail;
} LL_t;


/**
 * Create a new node
 */
Node *node_new(int val);


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
int ll_append(LL_t *llp, int val);


/**
 * Add a new node to beginning of the LL as HEAD
 */
int ll_prepend(LL_t *llp, int val);


/**
 * Find a node in LL by it's index
 */
Node *ll_find_by_idx(LL_t *llp, size_t idx);


/**
 * Find a node in LL by it's value
 * (Recursive implementation)
 */
Node *ll_find_by_val_Rec(Node *np, int val);


/**
 * Find a node in LL by it's value
 */
Node *ll_find_by_val(LL_t *llp, int val);


/**
 * Insert a new node to LL with a specific index
 */
int ll_insert_at_idx(LL_t *llp, size_t idx, int val);


/**
 * Insert a new node after a specific Node in the LL
 */
int ll_insert_after_node(LL_t *llp, Node *np, int val);


/**
 * delete a value from LL by it's value
 */
int ll_delete_by_val(LL_t *llp, int val);


/**
 * Delete a node from LL by it's index
 */
int ll_delete_by_idx(LL_t *llp, size_t idx);


/**
 * Free a singly-linked-list from memory and 
 * it's nodes.
 */
void ll_free(Node *np);

#endif // LL_H
