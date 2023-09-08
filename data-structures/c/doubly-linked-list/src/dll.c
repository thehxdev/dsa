#include <stdint.h>
#include <stdlib.h>
#include <memory.h>
#include "dll.h"


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

    memmove(nn->data, val, size);
    nn->size = size;
    nn->next = NULL;
    nn->prev = NULL;

    return nn;
}


void node_free(Node *np) {
    if (np) {
        if (np->data) {
            free(np->data);
            np->data = NULL;
        }
        free(np);
        np = NULL;
    }
}


DLL_t *dll_new() {
    DLL_t *ndll = (DLL_t*) malloc(sizeof(DLL_t));
    if (ndll == NULL)
        return NULL;

    ndll->head = NULL;
    ndll->tail = NULL;

    return ndll;
}


int dll_append(DLL_t *dllp, void *val, size_t size) {
    int stat = 0;
    Node *nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }

    if (dllp->head == NULL) {
        dllp->head = nn;
        dllp->tail = nn;
        goto ret;
    }

    nn->prev = dllp->tail;
    dllp->tail->next = nn;
    dllp->tail = nn;

ret:
    return stat;
}


int dll_prepend(DLL_t *dllp, void *val, size_t size) {
    int stat = 0;
    Node *nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }

    if (dllp->head == NULL) {
        dllp->head = nn;
        dllp->tail = nn;
        goto ret;
    }

    dllp->head->prev = nn;
    nn->next   = dllp->head;
    dllp->head = nn;

ret:
    return stat;
}


Node *dll_findNodeByIdx(DLL_t *dllp, size_t idx) {
    if (dllp == NULL)
        return NULL;

    Node *tmp = dllp->head;
    if (idx == 0)
        goto ret;

    for (uint32_t i = 1; i <= idx; i++) {
        tmp = tmp->next;
        if (tmp == NULL)
            return NULL;
    }

ret:
    return tmp;
}


Node *dll_findNodeByVal(DLL_t *dllp, void *val, size_t size) {
    if (dllp == NULL || val == NULL || size == 0)
        return NULL;

    Node *tmp = dllp->head;
    while (tmp != NULL) {
        if (memcmp(tmp->data, val, size) == 0)
            return tmp;

        tmp = tmp->next;
    }

    return NULL;
}


Node *dll_findNodeByVal_Rec(Node *np, void *val, size_t size) {
    if (np == NULL || val == NULL || size == 0)
        return NULL;

    if (memcmp(np->data, val, size) != 0)
        dll_findNodeByVal_Rec(np->next, val, size);

    return np;
}


int dll_insertAtIdx(DLL_t *dllp, size_t idx, void *val, size_t size) {
    int stat = 0;
    if (dllp == NULL || val == NULL || size == 0) {
        stat = 1;
        goto ret;
    }

    if (idx == 0) {
        stat = dll_prepend(dllp, val, size);
        goto ret;
    }

    Node *tmp = dll_findNodeByIdx(dllp, idx);
    if (tmp == NULL) {
        stat = 1;
        goto ret;
    }

    if (tmp->next == NULL) {
        stat = dll_append(dllp, val, size);
        goto ret;
    }

    Node *nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }

    nn->next = tmp;
    nn->prev = tmp->prev;
    tmp->prev->next = nn;
    tmp->prev = nn;

    if (nn->next == NULL)
        dllp->tail = nn;

ret:
    return stat;
}


int dll_insertAfterNode(DLL_t *dllp, Node *np, void *val, size_t size) {
    int stat = 0;
    if (dllp == NULL || np == NULL || val == NULL || size == 0) {
        stat = 1;
        goto ret;
    }
    if (dllp->head == NULL) {
        stat = 1;
        goto ret;
    }

    Node *nn = node_new(val, size);
    if (nn == NULL) {
        stat = 1;
        goto ret;
    }

    nn->next = np->next;
    nn->prev = np;
    np->next->prev = nn;
    np->next = nn;

    if (nn->next == NULL)
        dllp->tail = nn;

ret:
    return stat;
}


int dll_deleteByVal(DLL_t *dllp, void *val, size_t size) {
    int stat = 0;
    if (dllp == NULL || val == NULL || size == 0) {
        stat = 1;
        goto ret;
    }
    if (dllp->head == NULL) {
        stat = 1;
        goto ret;
    }

    Node *tmp = dll_findNodeByVal(dllp, val, size);

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

    node_free(tmp);
ret:
    return stat;
}


int dll_deleteByIdx(DLL_t *dllp, size_t idx) {
    int stat = 0;
    if (dllp == NULL) {
        stat = 1;
        goto ret;
    }
    if (dllp->head == NULL) {
        stat = 1;
        goto ret;
    }
    Node *tmp = dll_findNodeByIdx(dllp, idx);
    if (tmp == NULL) {
        stat = 1;
        goto ret;
    }

    if (tmp->prev == NULL) {
        if (tmp->next != NULL) {
            tmp->next->prev = NULL;
            dllp->head = tmp->next;
            goto free_ret;
        }
        dllp->head = NULL;
        dllp->tail = NULL;
        goto free_ret;
    }

    tmp->prev->next = tmp->next;
    if (tmp->next) {
        tmp->next->prev = tmp->prev;
    }

free_ret:
    node_free(tmp);
ret:
    return stat;
}


int dll_deleteByAddr(DLL_t *dllp, Node *np) {
    int stat = 0;
    if (dllp == NULL || np == NULL) {
        stat = 1;
        goto ret;
    }
    if (dllp->head == NULL || dllp->tail == NULL) {
        stat = 1;
        goto ret;
    }

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
    node_free(np);

ret:
    return stat;
}


void dll_free_nodes(DLL_t *dllp, Node *np) {
    if (np != NULL) {
        dll_free_nodes(dllp, np->next);
        node_free(np);
    }
}


void dll_free(DLL_t *dllp) {
    if (dllp != NULL) {
        dll_free_nodes(dllp, dllp->head);
        free(dllp);
    }
}

