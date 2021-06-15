#include "liste.h"

#ifndef _QUEUE_H
#define _QUEUE_H


typedef struct queue{
    Node *head;
    Node *tail;
    int size;
}Queue;


Node* initNode(int value);
Queue *init_queue(int value);
int peek(Queue *q);
Queue* enQueue(Queue *q , int value);
Queue* deQueue(Queue *q);
int size(Queue *q);
void printQueue(Queue *q);
int first(Queue *q);
int last(Queue *q);
void freeQueue(Queue *q);

#endif