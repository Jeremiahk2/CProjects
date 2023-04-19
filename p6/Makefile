CC = gcc
CFLAGS = -Wall -std=c99 -g

gq: gq.o input.o queue.o types.o
	gcc -Wall -std=c99 -g gq.o input.o queue.o types.o -o gq

gq.o: gq.c input.h queue.h types.h

types.o: types.c types.h queue.h

queue.o: queue.c  queue.h input.h

input.o: input.c input.h

clean:
	rm -f gq.o
	rm -f types.o
	rm -f queue.o
	rm -f input.o
	rm -f output.txt
	
