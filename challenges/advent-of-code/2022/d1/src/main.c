#include <stdio.h>
#include <stdlib.h>
#include "solver.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-path>\n", argv[0]);
        return 1;
    }

    Btree *elves_calories;
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open %s file.\n", argv[1]);
        return 1;
    }

    elves_calories = make_elves_calories_tree(fp);
    Node *max_node = bt_max(elves_calories);
    printf("Part 1: %d\n", max_node->val);
    if (max_node->parent->left)
        printf("Part 2: %d\n", (max_node->val + max_node->parent->val + max_node->parent->left->val));


    fclose(fp);
    bt_free(elves_calories);
    return 0;
}
