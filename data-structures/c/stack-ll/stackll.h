/*
 * Stack implementation using Doubly-Linked-List
 */

#ifndef STACK_LL_H
#define STACK_LL_H

#include <stdlib.h>
#include <memory.h>

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
Node *node_new(void *val, size_t size) {
    if (val == NULL || size == 0)
        return NULL;

    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return NULL;

    nn->data = (void*) malloc(size);
    if (nn->data == NULL) {
        free(nn);
        return NULL;
    }

    memcpy(nn->data, val, size);
    nn->size = size;
    nn->next = NULL;
    nn->prev = NULL;

    return nn;
}


/*
 * Free a node from memory
 */
void node_free(Node *np) {
    if (np != NULL) {
        if (np->data != NULL)
            free(np->data);
        free(np);
    }
}


/*
 * Create a new stack instance
 */
Stack *stk_new() {
    Stack *ns = (Stack*) malloc(sizeof(Stack));
    if (ns == NULL)
        return NULL;

    ns->top = NULL;
    return ns;
}


/*
 * insert a new node to stack
 */
int stk_push(Stack *sp, void *val , size_t size) {
    int stat = 0;
    if (sp == NULL || val == NULL || size == 0) {
        stat = 1;
        goto ret;
    }

    Node *nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }

    if (sp->top == NULL) {
        nn->prev = NULL;
    } else {
        nn->prev = sp->top;
    }

    nn->next = NULL;
    sp->top = nn;

ret:
    return stat;
}


/*
 * Remove last node from stack and return it's address
 */
Node *stk_pop(Stack *sp) {
    if (sp == NULL)
        return NULL;

    Node *tmp = sp->top;
    if (tmp == NULL) {
        return NULL;
    }

    sp->top = tmp->prev;
    if (tmp->prev != NULL)
        tmp->prev->next = NULL;

    return tmp;
}


/*
 * Remove last node from stack and also delete it
 */
int stk_popD(Stack *sp) {
    if (sp == NULL)
        return 1;

    Node *tmp = sp->top;
    if (tmp == NULL)
        return 1;

    sp->top = tmp->prev;
    if (tmp->prev != NULL)
        tmp->prev->next = NULL;

    node_free(tmp);
    return 0;
}


/*
 * Free a stack and all of it's nodes
 */
void stk_free(Stack *sp) {
    if (sp != NULL) {
        Node *tmp  = sp->top;
        if (tmp == NULL)
            goto only_stack;
        Node *prev = tmp->prev;

        while (1) {
            node_free(tmp);
            tmp = prev;
            if (tmp == NULL)
                break;
            prev = tmp->prev;
        }
only_stack:
        free(sp);
    }
}

#endif
