CC=/usr/bin/gcc
CFLAGS=-g -std=c99

main: main.o process.o

main.o: main.c

process.o: process.c	

clean:
	rm -f main *.o


