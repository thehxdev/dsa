#include <stdio.h>
#include "list.h"
#include "solver.h"

#define BUFF_SIZE 128

List *parse_input(FILE *fp) {
    int tmp = 0;
    char buff[BUFF_SIZE] = { 0 };
    List *num_list = list_new(1000);

    while (fgets(buff, BUFF_SIZE, fp)) {
        tmp = atoi(buff);
        list_append(num_list, tmp);
    }

    return num_list;
}
