# MINIX MAKEFILE
PROG=   processes
SRCS=   main.c process.c

DPADD+= ${LIBDRIVER} ${LIBSYS}
LDADD+= -ldriver -lsys

MAN=

BINDIR?= /usr/sbin

CPPFLAGS+= -D_SYSTEM=1

.include <bsd.prog.mk>


# LINUX MAKEFILE
#CC=/usr/bin/gcc
#CFLAGS=-g -std=c99

#main: main.o process.o

#main.o: main.c

#process.o: process.c	

#clean:
#	rm -f main *.o


