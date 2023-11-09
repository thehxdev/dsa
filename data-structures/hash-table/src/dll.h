/*
 * Doubly Linked-List (DLL) implementation for Hash-Table keys
 */

#ifndef HT_DOUBLY_LL_H
#define HT_DOUBLY_LL_H

#include <stddef.h>


typedef struct __node {
    char *key;
    struct __node *next;
    struct __node *prev;
} Node;


typedef struct __dll {
    Node *head;
    Node *tail;
    size_t len;
    size_t cap;
} DLL;


/**
 * WARN!
 * Create a new node
 *
 * @key: key string
 *
 * @ret: new Node addr | NULL
 */
Node *node_new(const char *key);


/**
 * Free a Node from memory
 *
 * @np: address of a Node
 */
void node_free(Node *np);


/**
 * WARN!
 * Find a node with it's key
 *
 * @lp: a DLL address
 * @key: key string
 *
 * @ret: address of Node | NULL
 */
Node *dll_findby_key(DLL *lp, const char *key);


/**
 * WARN!
 * Create a new DLL
 *
 * @cap: capacity of DLL
 *
 * @ret: address of new DLL | NULL
 */
DLL *dll_new(size_t cap);


/**
 * WARN!
 * Add a new node to DLL
 *
 * @lp: a DLL address
 * @key: key string
 *
 * @ret: address of new Node | NULL
 */
Node *dll_add_key(DLL *lp, const char *key);


/**
 * Remove a node from DLL by it's key
 *
 * @lp: a DLL address
 * @key: key string
 *
 * @ret: 0 ok | 1 error
 */
int dll_remove_key(DLL *lp, const char *key);


/**
 * Remove a node from DLL by it's address
 *
 * @lp: a DLL address
 * @np: a Node address
 *
 * @ret: 0 ok | 1 error
 */
int dll_remove_node(DLL *lp, Node *np);


/**
 * Free a DLL from memory
 *
 * @lp: a DLL address
 *
 */
void dll_free(DLL *lp);

#endif // DOUBLY_LL_H
