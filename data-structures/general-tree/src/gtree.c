#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "gtree.h"


Node *node_new(int val) {
    Node *n = (Node*) malloc(sizeof(Node));
    if (n == NULL)
        return NULL;

    n->val = val;
    n->parent = NULL;
    n->children = nodelist_new(10);

    return n;
}


void nodes_free(Node *np) {
    if (np) {
        for (size_t i = 0 ; i < np->children->len; i++) {
            nodes_free(np->children->nodes[i]);
        }
        free(np->children->nodes);
        free(np->children);
        free(np);
    }
}


NodeList *nodelist_new(const size_t cap) {
    NodeList *nl = (NodeList*) malloc(sizeof(NodeList));
    if (nl == NULL)
        return NULL;

    nl->len = 0;
    nl->cap = cap;
    nl->nodes = (Node**) malloc(sizeof(Node*) * cap);
    if (nl->nodes == NULL) {
        free(nl);
        return NULL;
    }

    return nl;
}


void nodelist_free(NodeList *nlp) {
    if (nlp) {
        for (size_t i = 0; i < nlp->len; i++) {
            nodes_free(nlp->nodes[i]);
        }
        free(nlp->nodes);
        free(nlp);
    }
}

void nodelist_append(NodeList *nlp, Node *np) {
    if (nlp == NULL || np == NULL)
        return;

    if (nlp->len % nlp->cap == 0) {
        size_t new_size = sizeof(Node*) * (nlp->len + nlp->cap);
        nlp->nodes = (Node**) realloc(nlp->nodes, new_size);
    }

    // nlp->nodes[nlp->len] = (Node*) malloc(sizeof(Node));
    nlp->nodes[nlp->len] = np;
    nlp->len += 1;
}


GTree *tree_new() {
    GTree *gt = (GTree*) malloc(sizeof(GTree));
    if (gt == NULL)
        return NULL;

    gt->root = NULL;
    return gt;
}


Node *tree_add(GTree *gtp, int val, Node *parent) {
    if (gtp == NULL)
        return NULL;

    Node *n = node_new(val);
    if (n == NULL)
        return NULL;

    if (gtp->root == NULL) {
        gtp->root = n;
        return n;
    }

    if (parent == NULL) {
        free(n);
        return NULL;
    }
    n->parent = parent;
    nodelist_append(parent->children, n);
    return n;
}


// TODO: Complente this funciton
Node *tree_find(GTree *gtp, int val, Node *np);


void tree_free(GTree *gtp, Node *np) {
    if (np != NULL) {
        nodes_free(np);
    }
    free(gtp);
}


void tree_print(GTree *gtp, Node *np) {
    if (np != NULL) {
        printf("%d\n", np->val);
        for (size_t i = 0; i < np->children->len; i++)
            tree_print(gtp, np->children->nodes[i]);
    }
}
