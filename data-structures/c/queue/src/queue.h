/*
 * Queue implementation using doubly-linked-list
 */


#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct __node {
    void *data;
    struct __node *next;
    struct __node *prev;
} Node;


typedef struct __queue {
    Node *head;
    Node *tail;
} Queue;


Node *node_new(void *val, size_t size);

void node_free(Node *np);

Queue *q_new();

int q_enqueue(Queue *qp, void *val, size_t size);

Node *q_dequeue(Queue *qp);

int q_dequeueD(Queue *qp);

void q_free(Queue *qp);

#endif // QUEUE_H
