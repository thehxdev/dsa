#include <stdio.h>
#include <stdlib.h>
#include "btree.h"

int main(void) {
    BT_t *tree = bt_init();
    int iarr[] = {10, 2, 84, 1, 56, 6, 83, 23, 8, 3, 11, 90};
    size_t iarr_size = sizeof(iarr) / sizeof(iarr[0]);

    for (size_t i = 0; i < iarr_size; i++)
        bt_add(tree, tree->root, iarr[i]);

    bt_print(tree->root);

    printf("\nMax value: %d\n", bt_find_max(tree->root)->data);
    printf("Min value: %d\n", bt_find_min(tree->root)->data);

    bt_free(tree);
    return 0;
}
