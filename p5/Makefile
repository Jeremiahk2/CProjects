CC = gcc
CFLAGS = -Wall -std=c99 -g

fieldTest: fieldTest.o field.o
	gcc -Wall -std=c99  -g fieldTest.o field.o -o fieldTest

fieldTest.o: fieldTest.c field.c field.h
