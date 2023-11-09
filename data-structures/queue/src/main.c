#include <stdio.h>
#include <stdlib.h>
#include "queue.h"


int main(void) {
    Queue *q = q_new();

    for (int i = 0; i < 10; i++)
        q_enqueue(q, i);


    // rn -> removed node
    Node *rn = q_dequeue(q);

    Node *tmp = q->head;
    while (tmp != NULL) {
        printf("%d\n", tmp->data);
        tmp = tmp->next;
    }

    free(rn);
    q_free(q);
    return 0;
}
