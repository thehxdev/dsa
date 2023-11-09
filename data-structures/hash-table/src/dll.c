#include <stdlib.h>
#include <string.h>
#include "ht.h"
#include "dll.h"


Node *node_new(const char *key) {
    Node *node = (Node*) malloc(sizeof(Node));
    if (node == NULL)
        return NULL;

    node->key = (char*) calloc(sizeof(char), strlen(key));
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    strcpy(node->key, key);

    node->next = NULL;
    node->prev = NULL;

    return node;
}


void node_free(Node *np) {
    if (np == NULL)
        return;

    if (np->key)
        free(np->key);
    free(np);
}


Node *dll_findby_key(DLL *lp, const char *key) {
    if (lp == NULL || key == NULL)
        return NULL;

    Node *tmp = lp->head;
    while (tmp != NULL) {
        if (strcmp(tmp->key, key) == 0)
            return tmp;
        tmp = tmp->next;
    }

    return NULL;
}


DLL *dll_new(size_t cap) {
    DLL *list = (DLL*) malloc(sizeof(DLL));
    if (list == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->len  = 0;
    list->cap  = cap;

    return list;
}


Node *dll_add_key(DLL *lp, const char *key) {
    if (lp == NULL || key == NULL)
        return NULL;

    if (dll_findby_key(lp, key) || lp->len == lp->cap)
        return NULL;

    Node *node = node_new(key);
    if (node == NULL)
        return NULL;

    if (lp->head == NULL) {
        lp->head = node;
        lp->tail = node;
        return node;
    }

    lp->tail->next = node;
    node->prev = lp->tail;
    lp->tail = node;

    lp->len += 1;
    return node;
}

int dll_remove_key(DLL *lp, const char *key) {
    if (lp == NULL || key == NULL)
        return 1;

    Node *tmp = dll_findby_key(lp, key);
    if (tmp == NULL)
        return 1;

    if (tmp->prev)
        tmp->prev->next = tmp->next;
    if (tmp->next)
        tmp->next->prev = tmp->prev;

    if (lp->head == tmp)
        lp->head = tmp->next;
    if (lp->tail == tmp)
        lp->tail = tmp->prev;

    node_free(tmp);
    lp->len -= 1;
    return 0;
}


int dll_remove_node(DLL *lp, Node *np) {
    if (lp == NULL || np == NULL)
        return 1;

    if (np->prev)
        np->prev->next = np->next;
    if (np->next)
        np->next->prev = np->prev;

    if (lp->head == np)
        lp->head = np->next;
    if (lp->tail == np)
        lp->tail = np->prev;

    lp->len -= 1;
    return 0;
}


void dll_free(DLL *lp) {
    if (lp == NULL)
        return;

    Node *tmp = lp->head;
    if (tmp == NULL) {
        free(lp);
        return;
    }

    Node *next = tmp->next;
    while (1) {
        node_free(tmp);
        tmp = next;
        if (tmp == NULL)
            break;
        next = tmp->next;
    }
    free(lp);
}
