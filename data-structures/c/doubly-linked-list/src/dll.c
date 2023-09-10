#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "dll.h"

#define check_then_free(p) if((p)) free((p))

Node *node_new(int val) {
    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return NULL;

    nn->data = val;
    nn->next = NULL;
    nn->prev = NULL;

    return nn;
}


DLL_t *dll_new() {
    DLL_t *ndll = (DLL_t*) malloc(sizeof(DLL_t));
    if (ndll == NULL)
        return NULL;

    ndll->head = NULL;
    ndll->tail = NULL;

    return ndll;
}


int dll_append(DLL_t *dllp, int val) {
    Node *nn = node_new(val);
    if (nn == NULL)
        return 1;

    if (dllp->head == NULL) {
        dllp->head = nn;
        dllp->tail = nn;
        return 0;
    }

    nn->prev = dllp->tail;
    dllp->tail->next = nn;
    dllp->tail = nn;

    return 0;
}


int dll_prepend(DLL_t *dllp, int val) {
    Node *nn = node_new(val);
    if (nn == NULL)
        return 1;

    if (dllp->head == NULL) {
        dllp->head = nn;
        dllp->tail = nn;
    }

    dllp->head->prev = nn;
    nn->next   = dllp->head;
    dllp->head = nn;

    return 0;
}


Node *dll_find_by_idx(DLL_t *dllp, size_t idx) {
    if (dllp == NULL)
        return NULL;

    Node *tmp = dllp->head;
    if (idx == 0)
        return tmp;

    for (uint32_t i = 1; i <= idx; i++) {
        tmp = tmp->next;
        if (tmp == NULL)
            return NULL;
    }

    return tmp;
}


Node *dll_find_by_val(DLL_t *dllp, int val) {
    if (dllp == NULL)
        return NULL;

    Node *tmp = dllp->head;
    while (tmp != NULL) {
        if (tmp->data == val)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}


Node *dll_find_by_val_Rec(Node *np, int val) {
    if (np == NULL)
        return NULL;

    if (np->data != val)
        dll_find_by_val_Rec(np->next, val);

    return np;
}


int dll_insert_after(DLL_t *dllp, Node *np, int val) {
    if (dllp == NULL || np == NULL)
        return 1;
    if (dllp->head == NULL)
        return 1;

    Node *nn = node_new(val);
    if (nn == NULL)
        return 1;

    nn->next = np->next;
    nn->prev = np;
    np->next->prev = nn;
    np->next = nn;

    if (nn->next == NULL)
        dllp->tail = nn;

    return 0;
}


int dll_delete_by_val(DLL_t *dllp, int val) {
    if (dllp == NULL)
        return 1;
    if (dllp->head == NULL)
        return 1;

    Node *tmp = dll_find_by_val(dllp, val);

    if (tmp->prev == NULL && tmp->next == NULL) {
        dllp->head = NULL;
        dllp->tail = NULL;
    }
    else if (tmp->prev == NULL && tmp->next != NULL) {
        dllp->head = tmp->next;
        tmp->next->prev = NULL;
    }
    else if (tmp->prev != NULL && tmp->next == NULL) {
        dllp->tail = tmp->prev;
        tmp->prev->next = NULL;
    }
    else {
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }

    free(tmp);
    return 0;
}


int dll_delete(DLL_t *dllp, Node *np) {
    if (dllp == NULL || np == NULL)
        return 1;
    if (dllp->head == NULL || dllp->tail == NULL)
        return 1;

    /*
     * check if np is the only node in DLL
     * (it's also head and tail)
     */
    if (np->prev == NULL && np->next == NULL) {
        dllp->head = NULL;
        dllp->tail = NULL;
    }
    else if (np->prev == NULL && np->next != NULL) {
        np->next->prev = NULL;
        dllp->head = np->next;
    }
    else if (np->prev != NULL && np->next == NULL) {
        np->prev->next = NULL;
        dllp->tail = np->next;
    }
    else {
        np->prev->next = np->next;
        np->next->prev = np->prev;
    }

    free(np);
    return 0;
}


void dll_free_nodes(Node *np) {
    if (np != NULL) {
        dll_free_nodes(np->next);
        free(np);
    }
}


void dll_free(DLL_t *dllp) {
    if (dllp != NULL) {
        dll_free_nodes(dllp->head);
        free(dllp);
    }
}
