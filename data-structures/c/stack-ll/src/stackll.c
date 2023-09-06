#include <stdlib.h>
#include <memory.h>
#include "stackll.h"


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


void node_free(Node *np) {
    if (np != NULL) {
        if (np->data != NULL)
            free(np->data);
        free(np);
    }
}


Stack *stk_new() {
    Stack *ns = (Stack*) malloc(sizeof(Stack));
    if (ns == NULL)
        return NULL;

    ns->top = NULL;
    return ns;
}


int stk_push(Stack *sp, void *val , size_t size) {
    if (sp == NULL || val == NULL || size == 0) {
        return 1;
    }

    Node *nn = node_new(val, size);
    if (nn == NULL) {
        return 1;
    }

    if (sp->top == NULL) {
        nn->prev = NULL;
    } else {
        nn->prev = sp->top;
    }

    nn->next = NULL;
    sp->top = nn;

    return 0;
}


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


void stk_free(Stack *sp) {
    if (sp != NULL) {
        Node *tmp  = sp->top;
        if (tmp == NULL) {
            free(sp);
            return;
        }
        Node *prev = tmp->prev;

        while (1) {
            node_free(tmp);
            tmp = prev;
            if (tmp == NULL)
                break;
            prev = tmp->prev;
        }
        free(sp);
    }
}
