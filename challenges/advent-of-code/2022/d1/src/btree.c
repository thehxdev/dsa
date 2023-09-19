#include <stdio.h>
#include <stdlib.h>
#include "btree.h"


Btree *bt_init() {
    Btree *t = (Btree*) malloc(sizeof(Btree));
    if (!t)
        return NULL;
    t->root  = NULL;

    return t;
}


static Node *node_new(int val) {
    Node *n = (Node*) malloc(sizeof(Node));
    if (!n)
        return NULL;

    n->val  = val;
    n->parent = NULL;
    n->left   = NULL;
    n->right  = NULL;

    return n;
}


Node *bt_add(Btree *btp, Node *np, int val) {
    if (!btp)
        return NULL;

    if (btp->root == NULL) {
        Node *n   = node_new(val);
        btp->root = n;
        return n;
    }

    
    if (val < np->val && np->left == NULL) {
        Node *n   = node_new(val);
        n->parent = np;
        np->left  = n;
        return n;
    } else if (val >= np->val && np->right == NULL) {
        Node *n   = node_new(val);
        n->parent = np;
        np->right = n;
        return n;
    } else if (val < np->val && np->left != NULL) {
        bt_add(btp, np->left, val);
    } else if (val >= np->val && np->right != NULL) {
        bt_add(btp, np->right, val);
    }

    return NULL;
}


Node *bt_max(Btree *btp) {
    if (btp) {
        Node *max_node = btp->root;
        while (max_node->right != NULL) {
            max_node = max_node->right;
        }

        return max_node;
    }

    return 0;
}


static void bt_free_nodes(Node *np) {
    Node *r, *l;
    if (np) {
        r = np->right;
        l = np->left;

        bt_free_nodes(l);
        free(np);
        bt_free_nodes(r);
    }
}


void bt_free(Btree *btp) {
    if (btp) {
        bt_free_nodes(btp->root);
        free(btp);
    }
}


void bt_print(Node *np) {
    if (np) {
        bt_print(np->left);
        printf("%d\n", np->val);
        bt_print(np->right);
    }
}
