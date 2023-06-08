#include <stdio.h>
#include <stdlib.h>

#define vecTypeNum 0

#include "vector.h"

int main(void) {
    Vector vec = vecInit();
    vecAppend(&vec, 10);
    vecAppend(&vec, 34);

    vecPrint(&vec);

    vecDel(&vec);
    return EXIT_SUCCESS;
}
