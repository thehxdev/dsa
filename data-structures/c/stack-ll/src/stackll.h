/*
 * Stack implementation using Doubly-Linked-List
 */

#ifndef STACK_LL_H
#define STACK_LL_H

#include <stddef.h>

typedef struct __node {
    void *data;
    struct __node *prev;
    struct __node *next;
    size_t size;
} Node;


typedef struct __stack {
    Node *top;
} Stack;


/*
 * Create a new stack node
 */
Node *node_new(void *val, size_t size);


/*
 * Free a node from memory
 */
void node_free(Node *np);


/*
 * Create a new stack instance
 */
Stack *stk_new();


/*
 * insert a new node to stack
 */
int stk_push(Stack *sp, void *val , size_t size);


/*
 * Remove last node from stack and return it's address
 */
Node *stk_pop(Stack *sp);


/*
 * Remove last node from stack and also delete it
 */
int stk_popD(Stack *sp);


/*
 * Free a stack and all of it's nodes
 */
void stk_free(Stack *sp);

#endif
