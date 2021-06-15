#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
// Incluziunea headerelor necesare pentru a putea
// scrie toate functiile de mai jos
#include "graph.h"
#include "liste.h"
#include "queue.h"
#include "tree.h"
// Initializarea unui graf
Graph *initGraph(int n){
    // Alocare memorie pentru graf
    Graph *newGraph = (Graph *)malloc(sizeof(Graph));
    // Se lucreaza cu noduri incepand cu cifra "1"
    newGraph->numar = n + 1;
    // Se initializeaza numarul de noduri folosite cu 0
    newGraph->noduri_folosite = 0;
    // Se aloca memorie pentru numele fiecarui nod si lista de adiacenta a fiecarui nod
    newGraph->nameList = (char **)malloc(newGraph->numar * sizeof(char *));

    newGraph->list = (Node **)malloc(newGraph->numar*sizeof(Node*));
    int i;
    for( i = 1;i <= n;i++){
        newGraph->list[i] = NULL;
       
        newGraph->nameList[i] = NULL;
    }
    return newGraph;
}
// Functie pentru adaugarea unui nod in graf
Graph *addNode(Graph *graph, char *nume){
    // Daca graful este NULL , se initializeaza graful cu 1 pozitie
    // si se adauga nodul
    int i;
    if(graph == NULL){
        Graph *newGraph = initGraph(1);
        
        return addNode(newGraph,nume);
    }
    // Daca numarul de noduri din graf este egal cu capacitatea maxima
    if(graph->noduri_folosite >= graph->numar -1){
        int var = graph->noduri_folosite +1 ;
        //Se dubleaza capacitatea maxima
        graph->numar *= 2;
        //Se realoca memorie pentru liste de adiacenta si nume
        graph->list = (Node **)realloc(graph->list,graph->numar * sizeof(Node*));
        
        graph->nameList = (char **)realloc(graph->nameList,graph->numar * sizeof(char*));
        // Se initializeaza cu NULL toate campurile din acesti vectori
        for(;var < graph->numar;var++){
            graph->list[var] = NULL;
            
            graph->nameList[var] = NULL;
        }
    }
    // Daca nodul exista deja in graf se returneaza graful
    for( i = 1;i <= graph->noduri_folosite;i++){
        if(strcmp(graph->nameList[i], nume) == 0){
            return graph;
        }
    }
    // Daca nu exista se incrementeaza nr. de noduri folosite
    graph->noduri_folosite++;
    // Se aloca memorie si se copiaza numele Actorului in noul nod din 
    // nr. de noduri folosite
    graph->nameList[graph->noduri_folosite] = (char *)malloc((strlen(nume)+ 1) * sizeof(char));

    graph->nameList[graph->noduri_folosite] = strcpy(graph->nameList[graph->noduri_folosite], nume);

    return graph;
}
//Functia este folosita pentru adaugarea unui arc
Graph *addArc(Graph *graph, int x, int y){
    //Daca exista deja o muchie intre x si y se returneaza graph
    if(graph->list[x] != NULL){
        Node *tmp = graph->list[x];

        while(tmp != NULL){
            if(strcmp(tmp->nume,graph->nameList[y]) == 0){
                return graph;
            }
            
            tmp = tmp->next;
        }
    }
    // Se verifica daca x = y atunci nu putem avea o muchie
    if(x == y)
        return graph;
    // Initializarea de noduri pentru a putea fi adaugate in listele 
    // de adiacenta
    Node *newNode = initList(x,graph->nameList[x]);
    Node *secondNode = initList(y, graph->nameList[y]);
    // adaugarea la inceputul listelor de adiacenta
    secondNode->next = graph->list[x];
    graph->list[x] = secondNode;

    newNode->next = graph->list[y];
    graph->list[y] = newNode;

    return graph;
}
// Printarea unui graf -- FUNCTIE INUTILA pentru testele finale
void printGraph(Graph *graph){

    printf("Numar de noduri este = %d \n" , graph->noduri_folosite );
    int i;
    for(i = 1;i <= graph->noduri_folosite;i++){
        printf("%d : " , i);
        
        print_list(graph->list[i]);
        
        printf("\n");
    }
}
// Printarea listei formate din numar-nume a grafului -- INUTILA pentru
//testele finale
void printGraphList(Graph *graph){

    printf("Numar de noduri este = %d \n" , graph->noduri_folosite - 1);
    int i;
    for( i = 1;i <= graph->noduri_folosite;i++){
        printf("%d : %s \n", i , graph->nameList[i]);
        
    }
}
// Dezalocarea memoriei unui graf
void freeGraph(Graph *graph){
    // Dezalocarea numelor si a listelor de adiacenta utilizand o functie
    // din liste.c
    int i;
    for( i = 1;i < graph->numar;i++){
        freeList(graph->list[i]);
        
        free(graph->nameList[i]);
    }
    free(graph->nameList);
    
    free(graph->list);
    
    free(graph);
}
// Eliminarea unui nod -- FUNCTIE INUTILA pentru testele finale
Graph *eliminare(Graph *graph , int x , int y){

    Node *first = graph->list[x];
    
    Node *second = graph->list[y];
    
    Node *tmp;
    
    if(graph->list[x] != NULL){
        if(first->data == y){
            tmp = first;
            
            graph->list[x] = graph->list[x]->next;
            
            free(tmp->nume);
            
            free(tmp);
        }
     }
    if(graph->list[y] != NULL){
        if(second->data == x){
            tmp = second;
            
            graph->list[y] = graph->list[y]->next;
            
            free(tmp->nume);
            
            free(tmp);
        }
    }

     if(graph->list[x] != NULL){     
        tmp = first;
        
        first = first->next;
        
        while(first != NULL){
            if(first->data == y){
                tmp->next = first->next;
              
                free(first->nume);
              
                free(first);
              
                break;
            }
            tmp = tmp->next;
            
            first = first->next;
        }
    }

     if(graph->list[y] != NULL){
        tmp = second;
        
        second = second->next;

        while(second != NULL){
            if(second->data == x){
                tmp->next = second->next;
                
                free(second->nume);
               
                free(second);
               
                break;
            }
            tmp = tmp->next;
           
            second = second->next;
        }
     }
    return graph;
}
// Functie pentru eliminarea unui nod -- INUTILA pentru testele finale
Graph *eliminareNod(Graph *graph , int v){
    int i;
    for( i = 1;i < graph->numar;i++){
        graph = eliminare(graph,i,v);
    }
    graph->list[v] = NULL;

    return graph;
}
// Functie pentru a afla gradul unui nod -- INUTILA
int grad(Graph *graph , int v){

    return length_list(graph->list[v]);
}
// Se foloseste pentru a afla numarul corespondent unui "nume"
int numarReferinta(Graph *graph,char *nume){

    if(graph == NULL) 
        return -1;
    int i;
    for(i = 1; i <= graph->noduri_folosite;i++){
        if(strcmp(graph->nameList[i], nume) == 0){
            return i;
        }
    }
    return -1;
}
// Se foloseste pentru a afla numele corespondent unui "numar"
char *getName(Graph *graph,int nod){

    return graph->nameList[nod];
}
// Functie utilizata la taskul1
Node *biggestConnectedComponent(Graph *graph){
    // Vector pentru a vedea daca un nod este vizitat
    int visited[graph->noduri_folosite + 1];
    // Doua liste in care se vor stoca
    // nodurile vizitate intr-un ciclu de DFS
    Node *first = NULL;
    
    Node *second = NULL;
    
    int i;

    for(i = 1; i <= graph->noduri_folosite;i++){
        visited[i] = 0;
    }

    for(i = 1;i <= graph->noduri_folosite;i++){
        //Daca un nod nu este inca vizitat
        if(visited[i] == 0){
            // Daca prima lista este vida , se apeleaza dfs cu "first"
            if(first == NULL){
                 DFSUtil(graph,i,visited,&first);
            
            }else{
                //Daca lista second este NULL se apeleaza dfs cu "second"
                if(second == NULL){
                    DFSUtil(graph,i,visited,&second);
                // Daca ambele liste au fost folosite 
                }else{
                    // Se verifica care are dimensiunea mai mare
                    // si se pastreaza cea mai lunga
                    if(length_list(first) > length_list(second)){
                        freeList(second);
                        
                        second = NULL;
                       
                        DFSUtil(graph,i,visited,&second);
                    }else{
                        freeList(first);
                        
                        first = NULL;
                        
                        DFSUtil(graph,i,visited,&first);
                    }
                }
            }
            //printf("\n");
        }
    }
    // Se verifica la final care lista este mai lunga pentru a 
    // se returna un rezultat si a se dezaloca memorie
    if(length_list(first) > length_list(second)){
        freeList(second);
        
        return first;
    }
    freeList(first);
    
    return second;
}
// Functia recursiva de dfs
void DFSUtil(Graph *graph,int nod, int* visited,Node **head){
    // Se marcheaza nodul "nod" ca fiind vizitat
    visited[nod] = 1;
    // Se adauga nodul (numar,nume) la lista head
    *head = list_append(*head,nod, getName(graph, nod));

    Node *it = graph->list[nod];

    while(it != NULL){
        if(visited[it->data] == 0)
            DFSUtil(graph,it->data,visited,head);
        
        it = it->next;
    }
}
// Functie pentru stergerea unui caracter
char* removeChar(char *str, char garbage) {

    char *src, *dst;
    
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        
        if (*dst != garbage) 
            dst++;
    }
    *dst = '\0';

    return str;
}
// Functie pentru determinarea celei mai scurte distante
// Se foloseste la taskul2
int shortestDistance(Graph *graph, char *numeX, char *numeY){
    // Se afla indicele nodurilor cu numeX si numeY
    int x = numarReferinta(graph, numeX);
    int y = numarReferinta(graph, numeY);
    // Se initializeaza vectori pentru vizitati si distante
    int visited[graph->noduri_folosite + 1];

    int distance[graph->noduri_folosite + 1];

    int i;
    for( i = 1;i <= graph->noduri_folosite;i++){
        visited[i] = 0;
       
        distance[i] = 0;
    }

    Queue *q = NULL;
    
    q = enQueue(q,x);

    visited[x] = 1;

    while(q != NULL){
        int top = first(q);

        q = deQueue(q);

        Node *it = graph->list[top];

        while(it != NULL){
            if(visited[it->data]){
                it = it->next;
                
                continue;
            }
            distance[it->data] = distance[top] + 1;
            
            q = enQueue(q,it->data);
           
            visited[it->data] = 1;
        }
    }
    // Daca nu exista drum de la x la y atunci se returneaza -1
    if(distance[y] == 0)
        return -1;

    return distance[y];
}
// Functie a determina puntile , se foloseste la taskul3
Tree* punti(Graph *graph){
    // Initializarea unei liste de tip Tree , structura este in tree.h
    Tree *Pair = NULL;
    
    int timp = 0,i;
    
    int index[graph->noduri_folosite+ 1];
    
    int low[graph->noduri_folosite + 1];
   
    int parinte[graph->noduri_folosite + 1];
    // Initializarea vectorilor de mai sus
    for(i = 1;i <= graph->noduri_folosite;i++){
        index[i] = -1;
        
        low[i] = INT_MAX;
       
        parinte[i] = -1;
    }
    
    for(i = 1;i <= graph->noduri_folosite;i++){
        // Daca nodul i este inca alb
        if(index[i] == -1)
            // Se apeleaza dfsB din nodul i
            dfsB(graph,i,timp,index,low,parinte,&Pair);
    }
    return Pair;
}
// Functie auxiliara pentru dfsB
int min(int a,int b){

    return a < b ? a : b;
}
// Functia dfsB este folosita pentru a parcurge in adancime graful
// si a adauga perechile de tip (u,v) ce sunt muchii critice
void dfsB(Graph *graph, int v,int timp,int* index, int* low, int*parinte,Tree **pair){

    index[v] = timp;
   
    low[v] = timp;
   
    timp++;
        
    Node *it = graph->list[v];

    while(it != NULL){
        if(it->data != parinte[v]){
            if(index[it->data] == -1){ 
                parinte[it->data] = v;
                    
                dfsB(graph,it->data,timp,index,low,parinte,pair);
                    
                low[v] = min(low[v],low[it->data]);

                if(low[it->data] > index[v]){
                    //printf("%s -- %s" , getName(graph,v), getName(graph,it->data));
                    // Se verifica alfabetic care nod sa fie scris primul in nod
                    if(strcmp(getName(graph,v), getName(graph,it->data)) < 0) 
                        *pair = addPair(*pair,removeChar(getName(graph,v),'\n') , removeChar(getName(graph,it->data),'\n'));
                    else
                        *pair = addPair(*pair,removeChar(getName(graph,it->data),'\n') , removeChar(getName(graph,v),'\n'));        
                }
            }else{
                low[v] = min(low[v] , index[it->data]);
            }
        }
        it = it->next;
    }    
}