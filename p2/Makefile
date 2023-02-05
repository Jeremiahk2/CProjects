CC = gcc
CFLAGS = -Wall -std=c99 -g

all: infix_10 infix_12

infix_10: infix.o number_10.o operation.o
	gcc -Wall -std=c99  -g infix.o number_10.o operation.o -o infix_10

infix.o: infix.c number.h operation.h
number_10.o: number_10.c number.h operation.h
operation.o: operation.c operation.h

infix_12: infix.o number_12.o operation.o
	gcc -Wall -std=c99 -g infix.o number_12.o operation.o -o infix_12

number_12.o: number_12.c number.h operation.h

clean:
	rm -f number_10.o
	rm -f number_12.o
	rm -f operation.o
	rm -f infix.o
	rm -f infix_10
	rm -f infix_12
	rm -f output.txt