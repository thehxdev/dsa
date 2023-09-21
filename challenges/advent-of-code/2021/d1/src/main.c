#include <stdio.h>
#include <stdlib.h>
#include "solver.h"
#include "list.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-path>\n", argv[0]);
        return 1;
    }

    List *depth_list = NULL;
    int increses_count = 0;
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] could not open file %s\n", argv[0]);
        return 1;
    }

    depth_list = parse_input(fp);

    // Part 1
    for (size_t i = 1; i < depth_list->len; i++) {
        if (depth_list->nums[i] > depth_list->nums[i - 1])
            increses_count++;
    }
    printf("Part 1: %d\n", increses_count);


    // Part Tow
    increses_count = 0;
    int sum = 0;
    List *three_depth_sum_list = list_new(200);

    for (size_t i = 0; i < depth_list->len - 2; i++) {
        sum = depth_list->nums[i] + depth_list->nums[i + 1] + depth_list->nums[i + 2];
        list_append(three_depth_sum_list, sum);
    }
    for (size_t i = 1; i < three_depth_sum_list->len; i++) {
        if (three_depth_sum_list->nums[i] > three_depth_sum_list->nums[i - 1])
            increses_count++;
    }
    printf("Part 2: %d\n", increses_count);

    fclose(fp);
    list_free(depth_list);
    list_free(three_depth_sum_list);
    return 0;
}
