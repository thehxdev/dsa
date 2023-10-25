#ifndef UTIL_H
#define UTIL_H


#include <stdio.h>
#include <stdint.h>
#include "list.h"

List *parse_input(FILE *fp);

size_t process_initial_state(List *lp, size_t days);

#endif // UTIL_H
