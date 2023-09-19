#include <stdio.h>
#include <stdlib.h>
#include "btree.h"
#include "solver.h"

#define BUFF_SIZE 128

Btree *make_elves_calories_tree(FILE *input) {
    Btree *elves_tree = bt_init();

    char buff[BUFF_SIZE] = { 0 };
    int current_calori = 0;
    int current_sum = 0;

    while (fgets(buff, BUFF_SIZE, input)) {
        if (buff[0] == '\n') {
            bt_add(elves_tree, elves_tree->root, current_sum);
            current_sum = 0;
            continue;
        }
        current_calori = atoi(buff);
        current_sum += current_calori;
    }

    return elves_tree;
}
