CC = gcc
CFLAGS = -Wall -std=c99 -g

fieldTest: fieldTest.o field.o
	gcc -Wall -std=c99  -g fieldTest.o field.o -o fieldTest

aesTest: aesTest.o aes.o fieldTest.o
	gcc -Wall -std=c99 -g aesTest.o aes.o field.o -o aesTest

aesTest.o: aesTest.c aes.h

aes.o: aes.c aes.h field.h io.h

fieldTest.o: fieldTest.c field.h

field.o: field.c field.h io.h

