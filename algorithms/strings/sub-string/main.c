#include <stdio.h>
#include <assert.h>


int str_substr_found_rec(char *source, char *query);

int str_substr_found(char *source, char *query);


int main(void) {
    int res;

    /* Test for recursive matcher */

    res = str_substr_found_rec("Hello World!", "Hello");
    assert(res == 1);

    res = str_substr_found_rec("Hello World!", "World!");
    assert(res == 1);

    res = str_substr_found_rec("Hello World!", "WoR");
    assert(res == 0);

    res = str_substr_found_rec("Hello World!", "o Wo");
    assert(res == 1);

    res = str_substr_found_rec("Hello World!", "Hello World!");
    assert(res == 1);

    printf("[OK] All tests for recursive function passed!\n");


    /* Test for loop based matcher */

    res = str_substr_found("Hello World!", "Hello World!");
    assert(res == 1);

    res = str_substr_found("Hello World!", "H World!");
    assert(res == 0);

    res = str_substr_found("Hello World!", "llo");
    assert(res == 1);

    res = str_substr_found("Hello World!", "rld.");
    assert(res == 0);

    printf("[OK] All tests for loop based function passed!\n");

    return 0;
}


// Recursive version
int str_substr_found_rec(char *source, char *query) {
    if (*source == '\0')
        return 0;

    if (*source == *query && *(query+1) == '\0')
        return 1;

    if (*source != *query) {
        source++;
        return str_substr_found_rec(source, query);
    }
    query++;
    return str_substr_found_rec(source, query);
}


// while loop version
int str_substr_found(char *source, char *query) {
    while (*source != *query && *source) source++;
    if (*source == '\0')
        return 0;
    while (*source == *query && *source && *query) {
        source++;
        query++;
    }
    return (*query == '\0');
}
