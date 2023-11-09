#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "btree.h"


Node *node_new(int val) {
    Node *n = (Node*) malloc(sizeof(Node));
    if (n == NULL)
        return NULL;

    n->data   = val;
    n->right  = NULL;
    n->left   = NULL;
    n->parent = NULL;

    return n;
}


BT_t *bt_init() {
    BT_t *nt = (BT_t*) malloc(sizeof(BT_t));
    if (nt == NULL)
        return NULL;

    nt->root = NULL;
    return nt;
}


Node *bt_find(Node *np, int val) {
    if (np == NULL)
        return NULL;

    if (np->data == val)
        return np;

    if (np->data > val)
        return (bt_find(np->left, val));
    else
        return (bt_find(np->right, val));
}

int bt_add(BT_t *btp, Node *np, int val) {
    if (btp == NULL)
        return 1;

    if (btp->root == NULL) {
        Node *nn = node_new(val);
        btp->root = nn;
        return 0;
    }

    if (val < np->data && np->left == NULL) {
        Node *nn = node_new(val);
        nn->parent = np;
        np->left = nn;
        return 0;
    } else if (val >= np->data && np->right == NULL) {
        Node *nn = node_new(val);
        nn->parent = np;
        np->right = nn;
        return 0;
    } else if (val < np->data && np->left != NULL) {
        bt_add(btp, np->left, val);
    } else if (val >= np->data && np->right != NULL) {
        bt_add(btp, np->right, val);
    }

    return 1;
}


static void bt_free_nodes(Node *np) {
    Node *r, *l;
    if (np != NULL) {
        r = np->right;
        l = np->left;

        bt_free_nodes(l);
        free(np);
        bt_free_nodes(r);
    }
}

void bt_free(BT_t *btp) {
    bt_free_nodes(btp->root);
    free(btp);
}


void bt_print(Node *np) {
    if (np != NULL) {
        bt_print(np->left);
        printf("%d\n", np->data);
        bt_print(np->right);
    }
}


Node *bt_find_max(Node *np) {
    if (np == NULL)
        return NULL;

    Node *max = np;
    while (max->right != NULL) {
        max = max->right;
    }
    return max;
}


Node *bt_find_min(Node *np) {
    if (np == NULL)
        return NULL;

    Node *min = np;
    while (min->left != NULL) {
        min = min->left;
    }
    return min;
}
