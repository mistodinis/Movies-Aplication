#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "liste.h"
#include "graph.h"
#include "queue.h"
#include "tree.h"

// Functie de comparare pentru functia qsort
// Se foloseste la taskul1 si taskul3
int stringCompare(const void *a, const void *b) {

    const char **ia = (const char **)a;
    const char **ib = (const char **)b;

    return strcmp(*ia, *ib);
}

int main(int argc, char *argv[]){
    // Initializarea grafului
    Graph *graph = initGraph(1);
    int i ,j ;
    
    FILE *fout, *fin;
    // Se deschid fisierele
    if(argv[2])
        fin = fopen(argv[2], "r");
    
    if(argv[3])
        fout = fopen(argv[3], "w");
    // Daca fisierul de input nu este deschis se termina programul
    if(fin == NULL){
        printf("Nu se poate deschide fisierul!\n");
        exit(1);
    }
    // Variabile folosite pentru citirea numarului de nr_filme
    // si a numarului de actori
    int nr_filme, nr_actori;

    char nr_filme_c[5];
    char nr_actori_c[5];
    // Citirea nr de filme
    fgets(nr_filme_c,sizeof(nr_filme_c),fin);
    // Convertirea la int 
    nr_filme = atoi(nr_filme_c);
    // Alocare memorie pentru 2 siruri , folosite pentru a citi din fisier
    char* film = (char*)malloc(100 * sizeof(char));
    
    char* numeActor = (char*)malloc ( 100 * sizeof (char));
    // Cat timp mai sunt filme de citit 
    // Constructia grafului
    while(nr_filme){
        // Se citeste numele filmului
        fgets(film,100* sizeof (char),fin);
        // Se citeste nr de actori
        fgets(nr_actori_c,sizeof(nr_actori_c), fin);
        // Conversie la int de la char[]
        nr_actori = atoi(nr_actori_c);
        // Alocarea memoriei pentru un vector de "nume"
        char **matrix = (char**)malloc ( (nr_actori + 1) * sizeof(char*));

        for( i = 1;i<= nr_actori;i++){
            matrix[i] = (char* )malloc ( 100 * sizeof (char));
        }
        int aux , aux2 = 1;
     
        aux = nr_actori;
        // Cat timp mai sunt actori in cadrul filmului actual de citit
        while(nr_actori){
            // Se citeste numele actorului
            fgets(numeActor,100*sizeof(char),fin);
            
            if(strcmp(numeActor,"\n")==0){
                continue;
            }
            // Se copiaza in matrix fiecare nume
            matrix[aux2] = strcpy(matrix[aux2], numeActor);
            // Se adauga nodul in graf
            graph = addNode(graph,numeActor);

            nr_actori--;
            
            aux2++;
        }
        // Se parcurg toate nodurile pentru a adauga
        // muchii intre toate nodurile din cadrul acestui film
        for( i = 1;i < aux2;i++){
            for( j = i+1;j < aux2;j++){
                // Se adauga arc intre noduri utilizand functia
                // numarReferinta , asa se afla numarul respectivului nod
                graph = addArc(graph,numarReferinta(graph,matrix[i]),numarReferinta(graph,matrix[j]));
            }
        }
        nr_filme--;
        // Dezalocarea memoriei pentru matrix
        for( i = 1;i <= aux;i++){
            free(matrix[i]);
        }
        free(matrix);
    }
    // Daca este accesat taskul1
     if(strcmp(argv[1], "-c1") == 0){
         // Se returneaza in task1 cea mai mare componenta conexa
        Node *task1 = biggestConnectedComponent(graph);
       
        Node *tmp = task1;
       
        int lengthT = length_list(task1);

        char **matrix = (char **)malloc((lengthT)*sizeof(char*));
        // se aloca memorie pentru matrix si se copiaza numele
        // din lista "task1"
        for( i = 0;i <lengthT;i++){ 
            matrix[i] = (char *)malloc ( 100 * sizeof (char));
            
            if(tmp != NULL){
                matrix[i] = strcpy(matrix[i],tmp->nume);
                
                tmp = tmp->next;
            }
        }
        // Se sorteaza vectorul de nume "matrix"
        qsort(matrix,lengthT ,sizeof(char*),stringCompare);

        char c[5];
        
        sprintf(c,"%d" , lengthT);
        // Se scrie in fisier
        fputs(c,fout);
        
        fputc('\n',fout);

        for( i = 0;i < lengthT;i++){
            fputs(matrix[i],fout);
        }
        // Dezalocarea memoriei folosite in aceasta bucla
        for( i = 0;i < lengthT;i++){
            free(matrix[i]);
        }
        free(matrix);

        freeList(task1);
     }
    // Daca este accesat taskul2
     if(strcmp(argv[1], "-c2") == 0){
        // Se aloca memorie pentru doua siruri
        char *numeX = (char*)malloc ( 100 * sizeof (char));
        char *numeY = (char*)malloc ( 100 * sizeof (char));
        // Se citesc cele doua nume din fisier
        fgets(numeX,100*sizeof(char),fin);
        fgets(numeY,100*sizeof(char),fin);

        char output[2];
        //se converteste la char dinstanta cea mai scurta intre 
        //cei doi actori
        sprintf(output,"%d", shortestDistance(graph,numeX,numeY));
        // Se scrie rezultatul in fisier
        fputs(output,fout);
        
        fputc('\n',fout);
        // Dezalocarea memoriei pentru cele doua siruri
        free(numeX);
        
        free(numeY);
     }
    // Daca este accesat taskul3
     if(strcmp(argv[1], "-c3") == 0){
        // Se returneaza in "pair" , puntile din graful "graph"
        Tree *pair = punti(graph);
        // Calculam lungimea listei
        int lungime = lengthPairs(pair);
        // Alocam doi vectori de siruri
        char **firstName = (char **)malloc( lungime* sizeof(char *));
       
        char **secondName = (char **)malloc( lungime * sizeof(char *));

        for( i = 0;i < lungime;i++){
            firstName[i] = (char *)malloc ( 100 * sizeof (char));
            
            secondName[i] = (char *)malloc ( 100 * sizeof (char));
        }

        Tree *it = pair; int counter = 0;
        // Se copiaza in primul vector toti actorii de pe prima pozitie
        // din toate nodurile pairs
        while(it){
            firstName[counter] = strcpy(firstName[counter], it->nume1);

            counter++;
            
            it = it->next;
        }
        // Sortam toate numele copiate anterior
       qsort(firstName,lungime,sizeof(char*),stringCompare);
         // Pentru fiecare nume din firstName
       for(i = 0; i < lungime;i++){
           it = pair;
           
           while(it){
               // Se navigheaza in lista pairs
               // Daca cele doua stringuri sunt egale
               if(strcmp(firstName[i],it->nume1) == 0){
                    // se copiaza in al 2-lea vector al 2-lea
                    // actor din nodul "it" de tip Tree
                    secondName[i] = strcpy(secondName[i],it->nume2);
                    // Se sterge nodul din lista pentru a nu
                    // lua de doua ori acelasi nod
                    pair = deleteSpecificPair(pair,it->nume1,it->nume2);
                    
                    break;
               }
                it = it->next;
           }
       }

        for(i = 0;i < lungime - 1;i++){ 
            // Daca exista un actor care formeaza doua punti
            // sau mai multe
            if(strcmp(firstName[i], firstName[i + 1]) == 0){
                int aux = i + 1;
                // Navigam prin firstname pana cand nu mai exista punti
                // Sau nodul firstname[i] nu mai formeaza noi punti
                while(aux < lungime){
                    if(strcmp(firstName[i], firstName[aux]) == 0){
                        aux++;

                    }else
                        break;
                }
                // Se sorteaza al 2-lea vector de siruri pe
                // pozitii specifice de la i pana la aux
                qsort(secondName + i,aux - i ,sizeof(char*),stringCompare);
                
                i = aux;
            }
                   
         }

        // for(int i = 0;i < lungime;i++){
        //     printf("(%s,%s)\n" , firstName[i] , secondName[i]);
        // }

        char nrPunti[5];
        
        sprintf(nrPunti,"%d" , lungime);
        //Se scrie in fisier nr. de punti
        fputs(nrPunti,fout);
        fputc('\n',fout);
        // Se scriu in fisier toate perechile care formeaza punti
        for( i = 0;i < lungime;i++){
            fputs(firstName[i],fout);
            
            fputc(' ',fout);
            
            fputs(secondName[i],fout);
            
            fputc('\n',fout);
        }
        // Dezalocam memoria folosita in aceasta bucla
        for( i = 0;i < lungime;i++){
            free(firstName[i]);
            
            free(secondName[i]);
        }

        free(firstName);
        
        free(secondName);
       
        freePairs(pair);
        
     }
    // Dezalocam ultimele chestii ramase
    freeGraph(graph);
    // Se inchid fisierele
    if(fin)
        fclose(fin);
    if(fout)
        fclose(fout);

    free(film);
    
    free(numeActor);
    
    return 0;
}