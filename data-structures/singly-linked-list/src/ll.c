#include <memory.h>
#include <stdlib.h>
#include <stdint.h>
#include "ll.h"

#define check_then_free(p) if ((p)) free((p))

Node *node_new(int val) {
    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return nn;

    nn->data = val;
    nn->next = NULL;
    return nn;
}


/**
 * Free a node from memory
 */
void node_free(Node *np) {
    check_then_free(np);
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
int ll_append(LL_t *llp, int val) {
    if (llp == NULL) {
        return 1;
    }

    // new node
    Node *nn = node_new(val);
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
int ll_prepend(LL_t *llp, int val) {
    if (llp == NULL)
        return 1;

    // new node
    Node *nn = node_new(val);
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
Node *ll_find_by_idx(LL_t *llp, size_t idx) {
    if (llp == NULL || idx < 0)
        return NULL;

    Node *tmp = llp->head;
    if (idx == 0)
        return tmp;

    for (uint32_t i = 1; i <= idx; i++) {
        tmp = tmp->next;
        if (tmp == NULL)
            break;
    }
    return tmp;
}


/**
 * Find a node in LL by it's value
 * (Recursive implementation)
 */
Node *ll_find_by_val_Rec(Node *np, int val) {
    if (np == NULL)
        return NULL;

    if (np->data != val)
        return ll_find_by_val_Rec(np->next, val);

    return np;
}


/**
 * Find a node in LL by it's value
 */
Node *ll_find_by_val(LL_t *llp, int val) {
    if (llp == NULL)
        return NULL;

    Node *tmp = llp->head;
    while (tmp != NULL) {
        if (tmp->data == val)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}


/**
 * Insert a new node to LL with a specific index
 */
int ll_insert_at_idx(LL_t *llp, size_t idx, int val) {
    if (llp == NULL) {
        return 1;
    }

    if (idx == 0) {
        ll_prepend(llp, val);
        return 0;
    }

    Node *tmp = ll_find_by_idx(llp, idx - 1);
    if (tmp == NULL)
        return 1;

    Node *nn = node_new(val);
    if (nn == NULL) {
        return 1;
    }
    nn->next = tmp->next;

    tmp->next = nn;
    if (nn->next == NULL)
        llp->tail = nn;

    return 0;
}


/**
 * Insert a new node after a specific Node in the LL
 */
int ll_insert_after_node(LL_t *llp, Node *np, int val) {
    if (np == NULL || llp == NULL) {
        return 1;
    }

    if (llp->head == NULL) {
        return 1;
    }

    Node *nn = node_new(val);
    if (nn == NULL) {
        return 1;
    }

    nn->next = np->next;
    np->next = nn;

    if (nn->next == NULL)
        llp->tail = nn;

    return 0;
}


/**
 * delete a value from LL by it's value
 */
int ll_delete_by_val(LL_t *llp, int val) {
    if (llp == NULL)
        return 1;

    Node *current = llp->head;
    if (current == NULL)
        return 1;
    Node *prev = NULL;

    while (1) {
        prev = current;
        current = current->next;

        if (current == NULL)
            return 1;

        if (current->data == val) {
            break;
        }
    }

    if (current == llp->head) {
        node_free(current);
        llp->head = NULL;
        llp->tail = NULL;
        return 0;
    }

    prev->next = current->next;
    if (current->next == NULL)
        llp->tail = prev;
    node_free(current);

    return 0;
}


/**
 * Delete a node from LL by it's index
 */
int ll_delete_by_idx(LL_t *llp, size_t idx) {
    if (llp == NULL) {
        return 1;
    }

    Node *tmp = llp->head;
    Node *prev = NULL;

    if (idx == 0) {
        llp->head = llp->head->next;
        if (llp->head == NULL)
            llp->tail = NULL;
        node_free(tmp);
        return 0;
    }

    for (uint32_t i = 1; i <= idx; i++) {
        prev = tmp;
        tmp = tmp->next;
        if (tmp == NULL)
            break;
    }

    if (tmp == llp->tail)
        llp->tail = prev;

    prev->next = tmp->next;
    node_free(tmp);

    return 0;
}


/**
 * Free a singly-linked-list from memory and 
 * it's nodes.
 */
void ll_free(Node *np) {
    if (np != NULL) {
        ll_free(np->next);
        node_free(np);
    }
}
