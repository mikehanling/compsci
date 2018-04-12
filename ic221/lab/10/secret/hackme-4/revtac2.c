#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

char * get_tmp(){
  char * tmp_path = malloc(PATH_MAX);
  srand(time(NULL));
  snprintf(tmp_path,PATH_MAX,"/tmp/icc221-lab11-tmp.%08u",rand());
  return tmp_path;
}

int main(int argc, char *argv[]){

  if( argc < 2){
    fprintf(stderr, "%s: ERROR: Require output file\n",argv[0]);
    exit(1);
  }

  char cmd1[100];
  char cmd2[100];

  
  char * tmp_path = get_tmp();
  char *p;
  for(p=argv[1];*p;p++){
    if(*p < 'a' || *p > 'z'){
      fprintf(stderr, "%s: ERROR: Only take ouput files in lowercase\n",argv[0]);
      exit(1);
    } 
  }
      

  printf("cmd1: %p\n",cmd1);
  printf("cmd2: %p\n",cmd2);
  sprintf(cmd2,"/home/scs/aviv/lab-11-secret/hackme-4/rev %s",tmp_path);
  sprintf(cmd1,"/usr/bin/tac %s > %s", argv[1],tmp_path);

  system(cmd1);
  system(cmd2);


  unlink(tmp_path);

  return 0;
}
