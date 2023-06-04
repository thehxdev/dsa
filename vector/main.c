#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "main.h"

int main(void) {
    Vector vec = vecInit();
    vecAppend(&vec, 80);


    vecPrint(&vec);

    vecDel(&vec);
    return OK;
}
