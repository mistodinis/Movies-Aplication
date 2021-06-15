CC = gcc
CFLAGS = -Wall  -g


build: movies

movies: movies.o liste.o graph.o queue.o tree.o
	$(CC) movies.o liste.o graph.o queue.o tree.o -o movies
	
movies.o: movies.c 

graph.o: graph.c 

liste.o: liste.c 

queue.o: queue.c 

tree.o: tree.c


run:
	./movies
	
valgrind:
	valgrind --leak-check=full --track-origins=yes -q --log-file=rezultat_valgrind.txt ./movies
	

clean:
	rm -f *.o movies  
