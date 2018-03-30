

all: isdir printmode printusername printgroupname printtime

isdir: isdir.c
	gcc -Wall isdir.c -o isdir

printmode: printmode.c
	gcc -Wall -lbsd printmode.c -o printmode

printusername: printusername.c
	gcc -Wall printusername.c -o printusername

printgroupname: printgroupname.c
	gcc -Wall printgroupname.c -o printgroupname

printtime: printtime.c
	gcc -Wall printtime.c -o printtime


clean:
	rm -f isdir printmode printusername printgroupname printtime *~
