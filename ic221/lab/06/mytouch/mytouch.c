#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

  //variable decleration
  struct stat sb;
  struct timeval tv[2];

  //TODO: Complete the touch operation

  //get state and create if not 
  if (stat(argv[1], &sb) < 0) {
    creat(argv[1], 0777);  //highest allowed by umask
    stat(argv[1], &sb);
  }

  //print current mod time
  printf("Last Modified: %s", ctime(&(sb.st_mtime)));

  //keep old access time in array
  //ti[0].tv_sec = sb.st_atime;

  //new mod time in array
  gettimeofday(&(tv[0]), NULL);
  gettimeofday(&(tv[1]), NULL);

  //set new times in file and stat again
  utimes(argv[1], tv);
  stat(argv[1], &sb);

  //print new mod time
  printf("New Modified: %s", ctime(&(sb.st_mtime)));

  return 0;
}

