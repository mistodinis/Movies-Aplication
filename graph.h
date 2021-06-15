#include "liste.h"
#include "tree.h"
#ifndef _GRAPH_H
#define _GRAPH_H


typedef struct graph{
    int numar;

    int noduri_folosite;

    char **nameList;
    
    Node **list;
}Graph;

Graph *initGraph(int n);
Graph *addArc(Graph *graph, int x , int y);
void printGraph(Graph *graph);
void freeGraph(Graph *graph);
Graph *eliminare(Graph *graph , int x , int y);
Graph *eliminareNod(Graph *graph , int v);
int grad(Graph *graph , int v);
void printGraphList(Graph *graph);
Graph *addNode(Graph *graph, char *nume);
int numarReferinta(Graph *graph,char *nume);
Node *biggestConnectedComponent(Graph *graph);
void DFSUtil(Graph *graph,int nod, int* visited,Node **head);
char *getName(Graph *graph,int nod);
char* removeChar(char *str, char garbage);
int shortestDistance(Graph *graph, char *numeX, char *numeY);
void dfsB(Graph *graph, int v,int timp,int* index, int* low, int*parinte,Tree** pair);
Tree* punti(Graph *graph);
int min(int a,int b);


#endif