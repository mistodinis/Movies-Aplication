#ifndef _LISTE_H
#define _LISTE_H

typedef struct node{
    int data;
    char *nume;
    struct node *next;
} Node;

Node *initList(int data,char *nume);
void print_list(Node *node);
Node *list_prepend(Node *head , int data,char *nume);
Node *list_append(Node *head , int data, char *nume);
Node *list_remove_first(Node *head);
Node *list_remove(Node *head, int data);
Node *list_reverse(Node *head);
int length_list(Node *head);
Node *task5(Node *head , int k);
void freeList(Node * head);


#endif