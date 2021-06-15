#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "queue.h"

// Aceasta sursa este folosita pentru liste folosite la taskul3

// Initializarea unei liste cu 2 nume (pentru punti)
Tree *initPair(char *nume1,char *nume2){

    Tree *newPair = (Tree *) malloc(sizeof(Tree));
    
    newPair->nume1 = (char *) malloc(100*sizeof(char));
    newPair->nume2 = (char *) malloc(100*sizeof(char));

    newPair->nume1 = strcpy(newPair->nume1,nume1);
    newPair->nume2 = strcpy(newPair->nume2,nume2);
    
    newPair->next = NULL;

    return newPair;
}
//Adaugarea unui nod in lista
Tree *addPair(Tree *Pairs, char *nume1,char *nume2){

    if(Pairs == NULL)
        return initPair(nume1,nume2);

    Tree *newPair = initPair(nume1,nume2);

    newPair->next = Pairs;

    Pairs = newPair;

    return Pairs;
}
//Stergerea primului nod din lista
Tree *deletePair(Tree *Pairs){

    if(Pairs == NULL)
        return NULL;

    Tree *tmp = Pairs;

    Pairs = Pairs->next;

    free(tmp->nume1);
    
    free(tmp->nume2);
    
    free(tmp);

    return Pairs;
}
//Stergerea unui anumit nod din lista 
Tree *deleteSpecificPair(Tree *Pairs,char *nume1,char *nume2){

    if(Pairs == NULL)
        return NULL;

    if(strcmp(Pairs->nume1,nume1) == 0 && strcmp(Pairs->nume2,nume2) == 0){
        return deletePair(Pairs);
    }

    Tree *prev = Pairs;
    Tree *tmp = Pairs;

    if(tmp->next == NULL)
        return Pairs;

    tmp = tmp->next;

    while(tmp){
        if(strcmp(tmp->nume1,nume1) == 0 && strcmp(tmp->nume2,nume2) == 0){
            prev->next = tmp->next;
            
            free(tmp->nume1);
            
            free(tmp->nume2);
            
            free(tmp);

            return Pairs;
        }
        tmp = tmp->next;
        
        prev = prev->next;
    }
    return Pairs;
}
// Dezalocarea memoriei pentru o lista
void freePairs(Tree *Pairs){

    if(Pairs == NULL)
        return;

    Pairs = deletePair(Pairs);

    freePairs(Pairs);
}
// Functie pentru a afla lungimea unei liste
int lengthPairs(Tree *Pairs){

    Tree *tmp = Pairs;

    int length = 0;

    while(tmp){
        length++;
       
        tmp = tmp->next;
    }
    return length;
}
// Printarea unei liste de acest tip -- INUTILA pentru testele finale
void printPairs(Tree *Pairs){

    if(Pairs == NULL)
        return;

    Tree *tmp = Pairs;

    while(tmp){
        printf("(%s,%s)\n" , tmp->nume1 , tmp->nume2);

        tmp = tmp->next;
    }

    printf("\n");
}


