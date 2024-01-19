#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "gvector.h"


int main(void) {
    GVec_t DEINIT_GVEC *vec = gvec_new(0); /* use default capacity */

    int num = 10;
    const char *str = "Hello World!";

    gvec_append(vec, (void*)&num, sizeof(num));
    gvec_append(vec, (void*)str, strlen(str) + 1);

    void *tmp = gvec_get(vec, 0);
    printf("Number: %d\n", *(int*)tmp);

    tmp = gvec_get(vec, 1);
    printf("String: %s\n", (char*)tmp);

    Val_t *last = gvec_pop(vec);
    assert(strcmp((char*)last->data, str) == 0);
    assert(vec->vals[1] == NULL);

    val_free(&last);
    return 0;
}
