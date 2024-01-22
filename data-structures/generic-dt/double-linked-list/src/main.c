#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dll.h"


int main(void) {
    Dll_t DLL_DEINIT_END *dll = dll_init();

    for (int i = 0; i < 10; i++)
        dll_append(dll, &i, sizeof(i));

    Node_t *tmp = dll->head;
    while (tmp) {
        printf("%d\n", *(int*)tmp->val->data);
        tmp = tmp->next;
    }

    int num = 1;
    Node_t *n = dll_find(dll, &num);
    assert((*(int*)n->val->data) == num);

    return 0;
}
