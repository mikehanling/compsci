#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/errno.h>
#include <fcntl.h>

#define BUFFSIZE 4096

int main(int argc, char * argv[]){
  
  //Variable Decleartion
  char buf[BUFFSIZE];
  int n, fd_src, fd_dest;
  struct stat fs;


  //TODO: Complete the copy program
  
  //get stat
  if (stat(argv[1], &fs)) {
    perror(argv[0]);
    return 1;
  }
  if( S_ISDIR(fs.st_mode) ){
    fprintf(stderr, "%s: %s: Is a directory\n", argv[0], argv[1]);
    return 2;
  }

  //open files
  fd_src = open(argv[1], O_RDONLY);
  if (fd_src < 0) {
    perror(argv[0]);
    return 3;
  }

  fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, fs.st_mode);
  fchmod(fd_dest, fs.st_mode);
  if (fd_dest < 0) {
    perror(argv[0]);
    return 4;
  }

  //read and write
  while((n = read(fd_src, buf, BUFFSIZE)) > 0)
    write(fd_dest, buf, n);
  
  //close files
  close(fd_src);
  close(fd_dest);

  return 0;
}
