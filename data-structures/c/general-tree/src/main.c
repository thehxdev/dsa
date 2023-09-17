#include <stdio.h>
#include <stdlib.h>
#include "gtree.h"


int main(void) {
    GTree *tree = tree_new();
    Node *root = tree_add(tree, 10, NULL);

    Node *r_ch1 = tree_add(tree, 20, root);
    Node *r_ch2 = tree_add(tree, 23, root);
    Node *r_ch3 = tree_add(tree, 56, root);
    Node *r_ch4 = tree_add(tree, 91, root);
    Node *ch1_ch1 = tree_add(tree, 10021, r_ch1);

    tree_print(tree, root);
    tree_free(tree, root);
    return 0;
}
