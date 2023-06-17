#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sys/types.h>
#include "vector.h"


int main(void) {
    vector_t vec1 = vec_new(STR_T);
    vector_t vec2 = vec_new(VOID_T);
    vector_t vec3 = vec_new(VOID_T);

    /* add an array to vec3 */
    int8_t myarr[4] = {1, 2, 3, 4};
    vec_append(&vec3, myarr, ARR_SIZE(myarr));

    /* pointer to myarr[] */
    int8_t *myarr_ptr = (int8_t *) vec_get(&vec3, 0);
    printf("%d\n", myarr_ptr[1]); /* 2 */

    char *str1 = (char *) malloc(32);
    char *str2 = (char *) malloc(32);
    strcpy(str1,  "Hello From C!");
    strcpy(str2, "Generic Vectors");

    /* add str1 and str2 to vec1 */
    vec_append(&vec1, str1, strlen(str1));
    vec_append(&vec1, str2, strlen(str2));

    /* remove original pointers for str1 and str2 */
    free(str1);
    free(str2);

    /* add vec1 to vec2
     * (vector in a vector) */
    vec_append(&vec2, &vec1, sizeof(vec1));
    vector_t *x = (vector_t *) vec_get(&vec2, 0); /* vec1 in vec2 */
    vec_reverse(x); /* reverse vec1 order */

    for (u_int64_t i = 0; i < x->length; i++) {
        printf("%ld -> %s\n", i, (char*)vec_get(x, i));
    }

    /* delete and free vectors */
    vec_delete(x);
    vec_delete(&vec2);
    vec_delete(&vec3);
    return EXIT_SUCCESS;
}

