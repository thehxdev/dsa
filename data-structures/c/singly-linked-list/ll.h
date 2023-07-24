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


LL_t *ll_new() {
    /* new linked list */
    LL_t *nll = (LL_t*) malloc(sizeof(LL_t));

    nll->head = NULL;
    nll->tail = NULL;

    return nll;
}


int ll_append(LL_t *llp, void *val, size_t size) {
    /* new node */
    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return 1;

    nn->data = (void*) malloc(size);
    if (nn->data == NULL)
        return 1;

    memcpy(nn->data, val, size);
    nn->size = size;
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


int ll_prepend(LL_t *llp, void *val, size_t size) {
    /* new node */
    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return 1;

    nn->data = (void*) malloc(size);
    if (nn->data == NULL)
        return 1;

    memcpy(nn->data, val, size);
    nn->size = size;
    nn->next = llp->head;

    llp->head = nn;
    if (llp->tail == NULL)
        llp->tail = nn;

    return 0;
}


Node *ll_findNodeByIdx(LL_t *llp, size_t idx) {
    Node *tmp = llp->head;
    for (uint32_t i = 0; i <= idx; i++) {
        if (tmp == NULL)
            return NULL;

        tmp = tmp->next;
    }

    return tmp;
}


Node *ll_findNodeByVal(LL_t *llp, void *val, size_t size) {
    Node *tmp = llp->head;
    while (tmp != NULL) {
        if (tmp->size != size)
            continue;

        if (memcmp(tmp->data, val, size) == 0)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}


// TODO
int ll_insert(LL_t *llp, size_t idx, void *val, size_t size);


// TODO
int ll_delete(LL_t *llp, size_t idx);


void ll_free(LL_t *llp) {
    if (llp->head != NULL) {
        Node *current = llp->head;
        Node *prev = NULL;
        while (1) {
            if (prev != NULL)
                free(prev);

            if (current->next == NULL) {
                free(current->data);
                free(current);
                break;
            }

            free(current->data);
            prev = current;
            current = current->next;
        }
    }
    free(llp);
}


#endif
