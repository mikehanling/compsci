# TODO 
# - runme.c depends on library.c
# - runme_too.c depend on library.c and fun.c

all: runme runme_too

runme: runme.o library.o
	gcc -Wall -g runme.c library.o -o runme

runme_too: runme_too.o library.o fun.o
	gcc -Wall -g runme_too.o library.o fun.o -o runme_too

runme.o: runme.c
	gcc -Wall -g -c runme.c -o runme.o

runme_too.o: runme_too.c
	gcc -Wall -g -c runme_too.c -o runme_too.o

library.o: library.c library.h
	gcc -Wall -g -c library.c -o library.o

fun.o: fun.c fun.h
	gcc -Wall -g -c fun.c -o fun.o

clean: 
	rm -f runme runme.o library.o
	rm -f runme_too runme_too.o fun.o
