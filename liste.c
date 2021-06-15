#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"

// Initializarea unei liste sau a unui nod intr-o lista
Node *initList(int data, char *nume){
    // Alocare memorie pentru nod / cap lista
    Node *node = (Node *)malloc(sizeof(struct node));

    node->data = data;
    // Alocare memorie pentru campul "nume"
    node->nume = (char *)malloc((strlen(nume) + 1)*(sizeof(char)));
    
    node->nume = strcpy(node->nume, nume);
    
    node->next = NULL;

    return node;
}
// Printarea unei liste -- INUTILA pentru testele finale
void print_list(Node *node){

    if(node == NULL)
        return;

    if(node->next == NULL){
        printf("(%d, %s) ->NULL" , node->data , node->nume);
        
        return;
    }
    Node *tmp = node;

    while (tmp->next != NULL)
    {
        printf("(%d, %s) ->" , tmp->data , tmp->nume);
        tmp = tmp->next;
    }
    printf("(%d, %s) ->NULL" , tmp->data , tmp->nume); 
}
// Adaugare nod la inceputul unei liste
Node *list_prepend(Node *head , int data, char *nume){
    // Caz de baza , daca lista este vida , se initializeaza o lista
    if(head == NULL)
        return initList(data,nume);

    Node *new_head = initList(data,nume);

    new_head->next = head;

    head = new_head;

    return head;
}
// Adaugarea unui nod la finalul unei liste
Node *list_append(Node *head , int data, char *nume){

    if(head == NULL)
        return initList(data,nume);

    Node *last_node = initList(data,nume);
    
    Node *tmp = head;
    
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = last_node;

    return head;
}
//Stergerea primului nod din lista
Node *list_remove_first(Node *head){
    //Caz de baza , daca lista este vida se returneaza NULL
    if(head == NULL)
        return head;
    //Daca lista contine un singur nod
    if(head ->next == NULL){
        free(head->nume);
        
        free(head);
        
        return NULL;
    }
    Node *tmp = head;

    head = head->next;
    
    free(tmp->nume);
    
    free(tmp);

    return head;
}
// Stergerea nodului cu valoarea "data" din lista
Node *list_remove(Node *head, int data){

    if(head == NULL)
        return head;
    // Daca data se afla in primul nod se sterge primul nod
    if(head->data == data){
        return list_remove_first(head);
    }

    Node *tmp = head;
    
    Node *prev = head;
    // Daca lista are un singur nod si deja s-a verificat ca nu
    // este in primul nod se returneaza lista altfel se incrementeaza
    // pointerul tmp
    if(tmp->next != NULL)
        tmp = tmp->next;
    
    else
        return head;
    // Daca exista nodul tmp si are diferita de valoarea "data"
    while (tmp != NULL && tmp->data != data)
    {
        if(tmp->next == NULL)
            break;
        tmp = tmp->next;
        
        prev = prev->next;
    }
    // tmp este la finalul listei sau este in nodul cu valoarea "data"
    // Se rupe legatura cu nodul tmp
    prev->next = tmp->next;
    // Se dezaloca memoria utilizata pentru tmp
    free(tmp->nume);
    
    free(tmp);

    return head;
}
// Inverseaza o lista -- INUTILA pentru testele finale
Node *list_reverse(Node *head){

    if(head == NULL)
        return head;

    if(head->next == NULL)
        return head;

    Node *new_head = list_reverse(head->next);
    
    head->next->next = head;
    
    head->next = NULL;

    return new_head;
}
// Returneaza lungimea unei liste
int length_list(Node *head){

    if(head == NULL)
        return 0;
    
    if(head->next == NULL)
        return 1;

    Node *tmp = head;
    
    int length = 0;

    while (tmp != NULL)
    {
        length++;
        
        if(tmp->next != NULL)
            tmp = tmp->next;
        
        else
            break;
    }
    return length;
}
// Functie INUTILA pentru testele finale
Node *task5(Node *head , int k){

    if(head == NULL)
        return head;
    
    if(head->next == NULL)
        return head;

    int nr_rotiri = length_list(head) -  (k % length_list(head)) - 1;
    
    Node *tmp = head;

    while (nr_rotiri > 0 && tmp != NULL)
    {
        nr_rotiri--;

        if(tmp->next != NULL)
            tmp = tmp->next;
        else
            break;
    }
        Node *new_head = tmp->next;
        tmp->next = NULL;
    
        tmp = new_head;

        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }

        tmp->next = head;

        return new_head;    
}
// Eliberarea memoriei folosita de lista "head"
void freeList(Node * head){

    if(head == NULL)
        return;

    if(head->next == NULL){  
        free(head->nume);
        
        free(head);
        
        return;
    }
    Node *tmp = head;

    while(head != NULL){
        head = head->next;
        
        if(tmp->nume != NULL)
            free(tmp->nume);
        
        free(tmp);
       
        tmp = head;
    }
}




