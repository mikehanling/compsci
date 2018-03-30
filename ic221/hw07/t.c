
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char * argv[]){
  pid_t cid;
  char * ls_args[] = {"ls", NULL, NULL};
  if(argc == 2){
    ls_args[1] = argv[1];
  }
  cid = fork();
  if( cid == 0 ){ /*child*/
    execvp(ls_args[0],ls_args);
    exit(1); /*error*/
  }

  /*parent*/
  int status;
  wait(&status);

  if(WIFEXITED(status)) {
    if(WEXITSTATUS(status) == 0)
      printf("EXISTS!\n");
    if(WEXITSTATUS(status) == 2)
      printf("DOES NOT EXIST!\n");
  }

  return 0;
}
