/*
 * Queue implementation using doubly-linked-list
 */


#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

typedef struct __node {
    int data;
    struct __node *next;
    struct __node *prev;
} Node;


typedef struct __queue {
    Node *head;
    Node *tail;
} Queue;


Node *node_new(int val);

Queue *q_new();

int q_enqueue(Queue *qp, int val);

Node *q_dequeue(Queue *qp);

int q_dequeueD(Queue *qp);

void q_free(Queue *qp);

#endif // QUEUE_H
