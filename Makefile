# Makefile for Conjunto program with AVL and LLRB support

all: conjunto.o avl.o llrb.o main.o
	gcc conjunto.o avl.o llrb.o main.o -o main -std=c99 -Wall
	rm *.o

conjunto.o:
	gcc -c Conjunto.c -o conjunto.o

avl.o:
	gcc -c AVL.c -o avl.o

llrb.o:
	gcc -c LLRB.c -o llrb.o

main.o:
	gcc -c main.c -o main.o

run: all
	./main

clean:
	rm -f *.o main
