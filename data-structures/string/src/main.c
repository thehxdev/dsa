#include <stdio.h>

/* str.h */
#include "str.h"

#define FREE_AT_THE_END __attribute__((cleanup(str_free)))


int main(void) {
    String FREE_AT_THE_END *s = str_new("hello from c!");
    String FREE_AT_THE_END *s2 = str_concat("hello ", "world!");

    str_capitalize(s);
    str_capitalize(s2);

    printf("%s\n%s\n", str_ptr(s), str_ptr(s2));
    return 0;
}
