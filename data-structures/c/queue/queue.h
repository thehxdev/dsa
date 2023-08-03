/*
 * Queue implementation using doubly-linked-list
 */


#ifndef QUEUE_H
#define QUEUE_H


#include <stdlib.h>
#include <memory.h>


typedef struct __node {
    void *data;
    struct __node *next;
    struct __node *prev;
} Node;


typedef struct __queue {
    Node *head;
    Node *tail;
} Queue;


Node *node_new(void *val, size_t size) {
    if (val == NULL || size == 0)
        return NULL;

    Node *nn = (Node*) malloc(sizeof(Node));
    if (nn == NULL)
        return NULL;

    nn->data = (void*) malloc(size);
    if (nn->data == NULL) {
        free(nn);
        return NULL;
    }

    memcpy(nn->data, val, size);
    nn->next = NULL;
    nn->prev = NULL;

    return nn;
}


void node_free(Node *np) {
    if (np) {
        if (np->data)
            free(np->data);
        free(np);
    }
}


Queue *q_new() {
    Queue *nq = (Queue*) malloc(sizeof(Queue));
    if (nq == NULL)
        return NULL;

    nq->head = NULL;
    nq->tail = NULL;

    return nq;
}


int q_enqueue(Queue *qp, void *val, size_t size) {
    if (qp == NULL || val == NULL || size == 0)
        return 1;

    Node *nn = node_new(val, size);

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

    node_free(rn);
    return 0;
}


void q_free(Queue *qp) {
    if (qp) {
        Node *tmp = qp->head;
        if (tmp == NULL)
            goto only_q;
        Node *next = tmp->next;

        while (1) {
            node_free(tmp);
            tmp = next;
            if (tmp == NULL)
                break;
            next = tmp->next;
        }
only_q:
        free(qp);
    }
}


#endif // QUEUE_H
