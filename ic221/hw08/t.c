#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
int main(){
  int fd_in = open("fight.txt",O_RDONLY);

  int fd_out = open("output.txt",O_WRONLY | O_TRUNC | O_CREAT,0755);
  char buf[1024];

  close(0);
  dup2(fd_in,0);

  close(1);
  dup2(fd_out,1);

  while(scanf("%s",buf) != EOF){
    printf("%s\n",buf);
  }

  return 0;

}
