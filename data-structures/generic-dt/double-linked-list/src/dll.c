#include <stdlib.h>
#include <memory.h>
#include "dll.h"

Dll_t *dll_init() {
    Dll_t *d = (Dll_t*) malloc(sizeof(Dll_t));
    if (is_null(d))
        return NULL;

    d->head = NULL;
    d->tail = NULL;

    return d;
}


static void dll_deinit_helper(Node_t *np) {
    if (np) {
        dll_deinit_helper((Node_t*)np->next);
        if (np->val) {
            check_then_free(np->val->data);
            free(np->val);
        }
        free(np);
    }
}


void dll_deinit(Dll_t **dllp) {
    Dll_t *tmp = *dllp;
    if (tmp) {
        dll_deinit_helper(tmp->head);
        free(tmp);
    }
}


static Node_t *node_new(void *val, size_t val_size) {
    Node_t *n = (Node_t*) malloc(sizeof(Node_t));
    if (is_null(n))
        return NULL;

    n->next = NULL;
    n->prev = NULL;

    n->val = (Value_t*) malloc(sizeof(Value_t));
    if (is_null(n->val)) {
        free(n);
        return NULL;
    }

    n->val->data = calloc(val_size, 1);
    n->val->size = val_size;
    if (is_null(n->val->data)) {
        free(n->val);
        free(n);
        return NULL;
    }

    memmove(n->val->data, val, val_size);
    return n;
}


int dll_append(Dll_t *dllp, void *val, size_t val_size) {
    Node_t *n = node_new(val, val_size);

    if (is_null(dllp->head)) {
        dllp->head = n;
        dllp->tail = n;
        return 0;
    }

    n->prev = dllp->tail;
    dllp->tail->next = n;
    dllp->tail = n;

    return 0;
}


Node_t *dll_find(Dll_t *dllp, void *val) {
    Node_t *tmp = dllp->head;
    while (tmp) {
        if ((memcmp(tmp->val->data, val, tmp->val->size)) == 0)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
