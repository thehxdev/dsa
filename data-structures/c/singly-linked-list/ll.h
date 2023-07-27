#ifndef LL_H
#define LL_H


#include <memory.h>
#include <stdlib.h>
#include <stdint.h>

struct __node {
    void *data;
    size_t size;
    struct __node *next;
};
typedef struct __node Node;


struct __ll {
    Node *head;
    Node *tail;
};
typedef struct __ll LL_t;


Node *node_new(void *val, size_t size) {
    if (val == NULL || size == 0)
        return NULL;

    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return nn;

    nn->data = (void*) malloc(size);
    if (nn->data == NULL) {
        free(nn);
        return NULL;
    }

    memcpy(nn->data, val, size);
    nn->size = size;
    nn->next = NULL;

    return nn;
}


/**
 * Free a node's space from memory
 */
void node_free(Node *np) {
    if (np) {
        if (np->data)
            free(np->data);
        free(np);
    }
}


/**
 * Create a new LL
 */
LL_t *ll_new() {
    /* new linked list */
    LL_t *nll = (LL_t*) malloc(sizeof(LL_t));

    nll->head = NULL;
    nll->tail = NULL;

    return nll;
}


/**
 * Add a new node to end of the LL as TAIL
 */
int ll_append(LL_t *llp, void *val, size_t size) {
    if (llp == NULL || val == NULL) {
        return 1;
    }

    // new node
    Node *nn = node_new(val, size);
    if (nn == NULL)
        return 1;
    nn->next = NULL;

    if (llp->head == NULL) {
        llp->head = nn;
        llp->tail = nn;
    } else {
        llp->tail->next = nn;
        llp->tail = nn;
    }

    return 0;
}


/**
 * Add a new node to beginning of the LL as HEAD
 */
int ll_prepend(LL_t *llp, void *val, size_t size) {
    if (llp == NULL || val == NULL) {
        return 1;
    }

    // new node
    Node *nn = node_new(val, size);
    if (nn == NULL)
        return 1;

    nn->next = llp->head;

    llp->head = nn;
    if (llp->tail == NULL)
        llp->tail = nn;

    return 0;
}


/**
 * Find a node in LL by it's index
 */
Node *ll_findNodeByIdx(LL_t *llp, size_t idx) {
    if (llp == NULL)
        return NULL;

    Node *tmp = llp->head;
    for (uint32_t i = 0; i < idx; i++) {
        tmp = tmp->next;
        if (tmp == NULL)
            break;
    }
    return tmp;
}


/**
 * Find a node in LL by it's value
 */
Node *ll_findNodeByVal(LL_t *llp, void *val, size_t size) {
    if (llp == NULL)
        return NULL;

    Node *tmp = llp->head;
    while (tmp != NULL) {
        if (tmp->size != size) {
            tmp = tmp->next;
            continue;
        }

        if (memcmp(tmp->data, val, size) == 0)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}


/**
 * Insert a new node to LL with a specific index
 */
int ll_insertAtIdx(LL_t *llp, size_t idx, void *val, size_t size) {
    int stat = 0;

    if (llp == NULL) {
        stat = 1;
        goto ret;
    }

    Node *current = llp->head;
    // New Node
    Node *nn = NULL;

    if (llp->head == NULL && idx == 0) {
        stat = ll_append(llp, val, size);
        goto ret;
    }
    else if (llp->head != NULL && idx == 0) {
        stat = ll_prepend(llp, val, size);
        goto ret;
    }

    for (uint32_t i = 1; i <= idx; i++) {
        current = current->next;
        /*
         * if insertion index is out of range
         * skip inserting and prevent segfault
         */
        if (current == NULL) {
            stat = 1;
            goto ret;
        }
    }

    nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }
    nn->next = current->next;

    current->next = nn;
    if (nn->next == NULL)
        llp->tail = nn;
ret:
    return stat;
}


/**
 * Insert a new node after a specific Node in the LL
 */
int ll_insertAfterNode(LL_t *llp, Node *np, void *val, size_t size) {
    int stat = 0;
    if (np == NULL || llp == NULL) {
        stat = 1;
        goto ret;
    }

    if (llp->head == NULL) {
        stat = 1;
        goto ret;
    }

    Node *nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }

    nn->next = np->next;
    np->next = nn;

    if (nn->next == NULL)
        llp->tail = nn;

ret:
    return stat;
}


/**
 * delete a value from LL by it's value
 */
int ll_deleteByVal(LL_t *llp, void *val, size_t size) {
    int stat = 0;

    if (llp == NULL) {
        stat = 1;
        goto ret;
    }

    if (llp == NULL || val == NULL || size <= 0) {
        stat = 1;
        goto ret;
    }

    Node *current = llp->head;
    if (current == NULL) {
        stat = 1;
        goto ret;
    }
    Node *prev = NULL;

    while (1) {
        prev = current;
        current = current->next;

        if (current == NULL) {
            stat = 1;
            goto ret;
        }

        if (memcmp(current->data, val, size) == 0) {
            break;
        }
    }

    if (current == llp->head) {
        node_free(current);
        llp->head = NULL;
        llp->tail = NULL;
        goto ret;
    }

    prev->next = current->next;
    if (current->next == NULL)
        llp->tail = prev;
    node_free(current);

ret:
    return stat;
}


/**
 * Delete a node from LL by it's index
 */
int ll_deleteByIdx(LL_t *llp, size_t idx) {
    int stat = 0;

    if (llp == NULL) {
        stat = 1;
        goto ret;
    }

    Node *current = llp->head;
    Node *prev = NULL;

    if (idx == 0) {
        llp->head = llp->head->next;
        if (llp->head == NULL)
            llp->tail = NULL;
        node_free(current);
        goto ret;
    }

    for (uint32_t i = 0; i < idx; i++) {
        prev = current;
        current = current->next;

        if (current == NULL) {
            stat = 1;
            goto ret;
        }
    }

    prev->next = current->next;
    node_free(current);

ret:
    return stat;
}


/**
 * Free a singly-linked-list from memory and 
 * it's nodes.
 */
void ll_free(LL_t *llp) {
    if (llp->head != NULL) {
        Node *current = llp->head;
        Node *prev = NULL;
        while (1) {
            if (prev != NULL)
                free(prev);

            if (current->next == NULL) {
                node_free(current);
                break;
            }

            free(current->data);
            prev = current;
            current = current->next;
        }
    }
    free(llp);
}

#endif // LL_H

