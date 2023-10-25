#include <stdlib.h>
#include <stdint.h>

#include "list.h"
#include "util.h"


List *parse_input(FILE *fp) {
    if (fp == NULL)
        return NULL;

    List *l = list_new(30);
    if (l == NULL)
        return NULL;

    char c;
    int tmp;
    while ((c = fgetc(fp)) != EOF) {
        if (c == ',' || c == '\n')
            continue;
        tmp = atoi(&c);
        list_append(l, tmp);
    }

    rewind(fp);
    return l;
}


uint64_t process_initial_state(List *lp, size_t days) {
    List *res = list_copy(lp);
    if (res == NULL)
        return 0;

    size_t new_fishes_count = 0;
    for (size_t i = 0; i < days; i++) {
        for (size_t j = 0; j < res->len; j++) {
            if (res->vals[j] == 0) {
                list_set(res, j, 6);
                new_fishes_count += 1;
            } else {
                list_set(res, j, res->vals[j] - 1);
            }
        }

        for (size_t z = 0; z < new_fishes_count; z++)
            list_append(res, 8);
        new_fishes_count = 0;
    }

    uint64_t answer = res->len;
    list_free(res);

    return answer;
}
