#ifndef BTREE_H
#define BTREE_H

#include <stdbool.h>
#include <stddef.h>


typedef struct __node {
    int data;
    struct __node *left;
    struct __node *right;
    struct __node *parent; // Optional
} Node;

typedef struct __btree {
    Node *root;
} BT_t;


Node *node_new(int val);

BT_t *bt_init();

Node *bt_find(Node *np, int val);

int bt_add(BT_t *btp, Node *np, int val);

void bt_free(BT_t *btp);

void bt_print(Node *np);

Node *bt_find_max(Node *np);

Node *bt_find_min(Node *np);

#endif // BTREE_H
