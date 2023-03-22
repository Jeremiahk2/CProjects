CC = gcc
CFLAGS = -Wall -std=c99 -g

schedule: schedule.o catalog.o input.o

schedule.o: catalog.h input.h schedule.c
catalog.o: catalog.c catalog.h input.h
input.o: input.c input.h

clean:
	rm -f schedule.o
	rm -f catalog.o
	rm -f input.o
	rm -f output.txt
	rm -f schedule