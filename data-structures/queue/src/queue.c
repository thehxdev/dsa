#include <stdlib.h>
#include <memory.h>
#include "queue.h"

#define check_then_free(p) if ((p)) free((p))

Node *node_new(int val) {
    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return NULL;

    nn->data = val;
    nn->next = NULL;
    nn->prev = NULL;

    return nn;
}


Queue *q_new() {
    Queue *nq = (Queue*) malloc(sizeof(Queue));
    if (nq == NULL)
        return NULL;

    nq->head = NULL;
    nq->tail = NULL;

    return nq;
}


int q_enqueue(Queue *qp, int val) {
    if (qp == NULL)
        return 1;

    Node *nn = node_new(val);

    if (qp->head == NULL) {
        qp->head = nn;
        qp->tail = nn;
        return 0;
    }

    nn->prev = qp->tail;
    qp->tail->next = nn;
    qp->tail = nn;

    return 0;
}


Node *q_dequeue(Queue *qp) {
    if (qp == NULL)
        return NULL;

    // rn -> removed node
    Node *rn = qp->head;
    if (rn == NULL)
        return NULL;

    qp->head = rn->next;
    if (rn->next)
        rn->next->prev = NULL;
    rn->next = NULL;

    return rn;
}


int q_dequeueD(Queue *qp) {
    if (qp == NULL)
        return 1;

    // rn -> removed node
    Node *rn = qp->head;
    if (rn == NULL)
        return 1;

    qp->head = rn->next;
    if (rn->next)
        rn->next->prev = NULL;
    rn->next = NULL;

    free(rn);
    return 0;
}


static void q_free_nodes(Node *np) {
    if (np != NULL) {
        q_free_nodes(np->next);
        free(np);
    }
}

void q_free(Queue *qp) {
    q_free_nodes(qp->head);
    free(qp);
}
