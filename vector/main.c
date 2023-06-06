#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(void) {
    Vector vec = vecInit();
    vecAppend(&vec, 80);
    vecAppend(&vec, 23);
    vecAppend(&vec, 1);
    vecInsert(&vec, 2, 10);

    vecPrint(&vec);

    vecDel(&vec);
    return EXIT_SUCCESS;
}
