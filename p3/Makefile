CC = gcc
CFLAGS = -Wall -std=c99 -g

ident: ident.o syntax.o io.o

ident.o: ident.c syntax.h io.h
syntax.o: syntax.c syntax.h io.h
io.o: io.c io.h

clean:
	rm -f ident.o
	rm -f syntax.o
	rm -f io.o
	rm -f output.txt
	rm -f ident