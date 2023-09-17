#ifndef GTREE_H
#define GTREE_H

/*
 * Implementation of a general Tree data-structure
 */


#include <stddef.h>

struct __node;

struct __node_list {
    struct __node **nodes;
    size_t len;
    size_t cap;
};
typedef struct __node_list NodeList;

struct __node {
    int val;
    struct __node *parent;
    NodeList *children;
};
typedef struct __node Node;


typedef struct __gtree {
    Node *root;
} GTree;


Node *node_new(int val);

void nodes_free(Node *np);

NodeList *nodelist_new(const size_t cap);

void nodelist_free(NodeList *nlp);

void nodelist_append(NodeList *nlp, Node *np);

GTree *tree_new();

Node *tree_add(GTree *gtp, int val, Node *parent);

Node *tree_find(GTree *gtp, int val, Node *np);

void tree_free(GTree *gtp, Node *np);

void tree_print(GTree *gtp, Node *np);

#endif
