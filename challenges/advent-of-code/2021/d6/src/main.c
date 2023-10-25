#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "util.h"
#include "list.h"

#define BUFF_SIZE 32

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-path>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        perror("[ERROR] Cannot open input file");
        return 1;
    }

    List *initial_state = parse_input(fp);
    if (initial_state == NULL) {
        fclose(fp);
        return 1;
    }

    uint64_t part_1_result = process_initial_state(initial_state, 80);
    printf("Part 1: %lu\n", part_1_result);

    list_free(initial_state);
    fclose(fp);
    return 0;
}
