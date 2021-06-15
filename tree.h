#include "queue.h"
#ifndef _TREE_H
#define _TREE_H

typedef struct tree {
	
    char *nume1;
    char *nume2;
	struct tree *next;

	
} Tree;

Tree *initPair(char *nume1,char *nume2);
Tree *addPair(Tree *Pairs, char *nume1,char *nume2);
Tree *deletePair(Tree *Pairs);
Tree *deleteSpecificPair(Tree *Pairs,char *nume1,char *nume2);
void freePairs(Tree *Pairs);
int lengthPairs(Tree *Pairs);
void printPairs(Tree *Pairs);
#endif