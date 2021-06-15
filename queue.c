#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "liste.h"
#include "queue.h"

// Node initialization
Node* initNode(int value){
    
    Node *new_node = (struct node*) malloc(sizeof(struct node));
    
    new_node->next = NULL;
    
    new_node->nume = NULL;
   
    new_node->data = value;

    return new_node;
}
// Queue initialization
Queue *init_queue(int value){

    Queue *new_queue = (struct queue*) malloc(sizeof(struct queue));
    
    Node *new_node = initNode(value);
    
    new_queue->head = new_node;
    
    new_queue->tail = new_node;
   
    new_queue->size = 1;

    return new_queue;
}
// Return head value
int peek(Queue *q){

    return q->head->data;
}
// add "value" in queue "q"
Queue* enQueue(Queue *q , int value){

    if(q == NULL)
        return init_queue(value);

    Node *new_node = initNode(value);

    q->tail->next = new_node;
    
    q->tail = q->tail->next;
    
    q->size++;

    return q;
}

// delete first element from queue "q"
Queue* deQueue(Queue *q){

    if(q == NULL)
        return NULL;

    if(q->size == 1){
        freeList(q->head);
      
        free(q);
  
        return NULL;
    }
    Node *tmp = q->head;
  
    q->head = q->head->next;
  
    free(tmp);
  
    q->size--;

    return q;
}
// return size of "q"
int size(Queue *q){
   
    return q->size;
}

void printQueue(Queue *q){

    if(q == NULL)
        return;
   
    Node *tmp = q->head;
   
    while(tmp != NULL){
        printf("%d " , tmp->data);
   
        if(tmp->next != NULL)
            tmp = tmp->next;
  
        else
            break;
    }
    printf("\n");
}

int first(Queue *q){

    if(q == NULL)
        return 0;
    
    return q->head->data;
}

int last(Queue *q){

    if(q == NULL)
        return 0;

    return q->tail->data;
}

void freeQueue(Queue *q){

    if (q == NULL)
        return;

    freeList(q->head);
  
    free(q);
}

