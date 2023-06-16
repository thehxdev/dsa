#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include "vector.h"


int main(void) {
    vector_t vec1 = vec_new(STR_T);
    vector_t vec2 = vec_new(VOID_T);

    /* add string to vec1 */
    char *str1 = (char *) malloc(32);
    char *str2 = (char *) malloc(32);
    strcpy(str1,  "Hello From C!");
    strcpy(str2, "Generic Vectors");

    vec_append(&vec1, str1, strlen(str1));
    vec_append(&vec1, str2, strlen(str2));

    /* remove original pointers */
    free(str1);
    free(str2);

    /* add vec1 to vec2
     * vector in a vector */
    vec_append(&vec2, &vec1, sizeof(vec1));
    vector_t *x = (vector_t *) vec_get(&vec2, 0); /* vec1 in vec2 */
    vec_reverse(x); /* reverse vec1 order */

    for (u_int64_t i = 0; i < x->length; i++) {
        printf("%ld -> %s\n", i, (char*)vec_get(x, i));
    }

    vec_delete(x); /* delete and free vec1 */
    vec_delete(&vec2); /* delete and free vec2 */
    return EXIT_SUCCESS;
}

