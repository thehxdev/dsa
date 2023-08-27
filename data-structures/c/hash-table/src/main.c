#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ht.h"


/*
 * WARNING!
 * This is a Hash-Table implementation with a simple
 * Hash function. So key collisions are possible.
 */

int main(void) {
    // create a new Hash-Table (HT)
    HT *ht = ht_new();

    int age = 20;
    char *name = "Hossein";
    char *username = "thehxdev";
    char *fav_langs[] = { "C", "Lisp", "Haskell", "Rust", "Golang" };

    // calculate `fav_langs` bytes
    size_t arr_size = sizeof(fav_langs) / sizeof(fav_langs[0]);
    size_t arr_bytes = sizeof(fav_langs);
    for (size_t i = 0; i < arr_size; i++) {
        arr_bytes += (strlen(fav_langs[i]) + 1);
    }

    // add each value to HT with it's key
    ht_add(ht, "age", &age, sizeof(age));
    ht_add(ht, "name", name, strlen(name) + 1);
    ht_add(ht, "username", username, strlen(username) + 1);
    ht_add(ht, "fav_langs", fav_langs, arr_bytes);

    // Get values from HT with kyes
    char *name_HT = (char*) ht_getval(ht, "name");
    char *username_HT = (char*) ht_getval(ht, "username");
    int age_HT = *(int*) ht_getval(ht, "age");

    // print values
    printf("name: %s\nusername: %s\nage: %d\n", name_HT, username_HT, age_HT);

    // get stored array in HT
    char **fav_langs_HT = (char**) ht_getval(ht, "fav_langs");
    // print it's values one by one
    printf("fav_langs = { ");
    for (size_t i = 0; i < arr_size; i++)
        printf("%s ", fav_langs_HT[i]);
    printf("}\n");
    fflush(stdout);

    // free the HT
    ht_free(ht, free);
    return 0;
}
