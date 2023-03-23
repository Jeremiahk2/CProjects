CC = gcc
CFLAGS = -Wall -std=c99 -g

schedule: schedule.o catalog.o input.o
	gcc -Wall -std=c99 schedule.o catalog.o input.o -o schedule

schedule.o: schedule.c catalog.h input.h
	gcc -Wall -std=c99 -g schedule.c -c

catalog.o: catalog.c catalog.h input.h
	gcc -Wall -std=c99 -g catalog.c -c

input.o: input.c input.h
	gcc -Wall -std=c99 -g input.c -c

clean:
	rm -f schedule.o
	rm -f catalog.o
	rm -f input.o
	rm -f output.txt
	rm -f schedule