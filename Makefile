# LINUX GCC PATH
CC=/usr/bin/gcc
# MINIX GCC PATH
#/usr/pkg/bin/gcc
CFLAGS=-g -std=c99

main: main.o process.o

main.o: main.c

process.o: process.c	

clean:
	rm -f main *.o

