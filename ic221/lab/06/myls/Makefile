#TODO: 
# -- Don't forget you need to compile with the -lbsd option for myls
# -- gcc -lbsd -g -Wall myls.c -o myls

all: myls

myls: myls.c
	gcc -Wall -g myls.c -o myls -lbsd

clean:
	rm -f myls
