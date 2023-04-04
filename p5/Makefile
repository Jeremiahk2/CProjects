CC = gcc
CFLAGS = -Wall -std=c99 -g

all: encrypt decrypt fieldTest aesTest

encrypt: encrypt.o aes.o field.o io.o
	gcc -Wall -std=c99 -g encrypt.o aes.o field.o io.o -o encrypt

decrypt: decrypt.o aes.o field.o io.o
	gcc -Wall -std=c99 -g encrypt.o aes.o field.o io.o -o decrypt

fieldTest: fieldTest.o field.o
	gcc -Wall -std=c99  -g fieldTest.o field.o -o fieldTest

aesTest: aesTest.o aes.o fieldTest.o
	gcc -Wall -std=c99 -g aesTest.o aes.o field.o -o aesTest

encrypt.o: encrypt.c aes.h field.h io.h

decrypt.o: decrypt.c aes.h field.h io.h

aesTest.o: aesTest.c aes.h

aes.o: aes.c aes.h field.h io.h

fieldTest.o: fieldTest.c field.h

field.o: field.c field.h io.h

io.o: io.c io.h

clean:
	rm -f io.o
	rm -f field.o
	rm -f fieldTest.o
	rm -f aes.o
	rm -f aesTest.o
	rm -f decrypt.o
	rm -f encrypt.o
	rm -f encrypt
	rm -f decrypt
	rm -f fieldTest
	rm -f aesTest