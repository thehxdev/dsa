#include <stdlib.h>
#include <memory.h>
#include "stackll.h"


Node *node_new(int val) {
    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return NULL;

    nn->data = val;
    nn->next = NULL;
    nn->prev = NULL;

    return nn;
}


Stack *stk_new() {
    Stack *ns = (Stack*) malloc(sizeof(Stack));
    if (ns == NULL)
        return NULL;

    ns->top = NULL;
    return ns;
}


int stk_push(Stack *sp, int val) {
    if (sp == NULL) {
        return 1;
    }

    Node *nn = node_new(val);
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

    free(tmp);
    return 0;
}


static void stk_free_nodes(Node *np) {
    if (np != NULL) {
        stk_free_nodes(np->prev);
        free(np);
    }
}

void stk_free(Stack *sp) {
    stk_free_nodes(sp->top);
    free(sp);
}
