/*
 * Solution for AOC 2021 Day 2
 * https://adventofcode.com/2021/day/2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 128

typedef struct __submarine {
    int horizontal;
    int depth;
    int aim;
} Submarine;

char *parse_command_num(const char *buff);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <input-file-path>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] Could not open %s file\n", argv[1]);
        return 1;
    }

    char *command_num_str = NULL;
    int command_num = 0;
    char buff[BUFF_SIZE] = { 0 };

    Submarine positionP1 = {
        .horizontal = 0,
        .depth = 0,
        .aim = 0,
    };

    Submarine positionP2 = {
        .horizontal = 0,
        .depth = 0,
        .aim = 0,
    };

    // Solve Part 1 and Part 2 with one loop
    while (fgets(buff, BUFF_SIZE, fp) != NULL) {
        command_num_str = parse_command_num(buff);
        command_num = atoi(command_num_str);
        switch (buff[0]) {
            case 'f':
                positionP1.horizontal += command_num;
                positionP2.horizontal += command_num;
                positionP2.depth += positionP2.aim * command_num;
                break;
            case 'd':
                positionP1.depth += command_num;
                positionP2.aim += command_num;
                break;
            case 'u':
                positionP1.depth -= command_num;
                positionP2.aim -= command_num;
                break;
            default: break;
        }
        free(command_num_str);
    }
    printf("Advent Of Code 2021 Day 2\n");
    printf("Part 1: %d\n", positionP1.depth * positionP1.horizontal);
    printf("Part 2: %d\n", positionP2.horizontal * positionP2.depth);

    fclose(fp);
    return 0;
}


char *parse_command_num(const char *buff) {
    char *tmp = strdup(buff);
    char *sptr;

    char *last = NULL;
    char *token = strtok_r(tmp, " ", &sptr);
    while (1) {
        token = strtok_r(NULL, " ", &sptr);
        if (token == NULL)
            break;
        last = token;
    }
    last = strdup(last);
    free(tmp);
    return last;
}
