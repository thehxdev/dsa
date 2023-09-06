#include <stdio.h>
#include "queue.h"


int main(void) {
    Queue *q = q_new();

    for (int i = 0; i < 10; i++)
        q_enqueue(q, &i, sizeof(int));


    // rn -> removed node
    Node *rn = q_dequeue(q);

    Node *tmp = q->head;
    while (tmp != NULL) {
        printf("%d\n", *(int*)tmp->data);
        tmp = tmp->next;
    }

    node_free(rn);
    q_free(q);
    return 0;
}
