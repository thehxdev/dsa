#ifndef AOC_2022_D1_BTREE_H
#define AOC_2022_D1_BTREE_H


typedef struct __node {
    int val;
    struct __node *left;
    struct __node *right;
    struct __node *parent;
} Node;


typedef struct __tree {
    Node *root;
} Btree;


Btree *bt_init();

Node *bt_add(Btree *btp, Node *np, int val);

Node *bt_max(Btree *btp);

void bt_free(Btree *btp);

void bt_print(Node *np);


#endif // AOC_2022_D1_BTREE_H
