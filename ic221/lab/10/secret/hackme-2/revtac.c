#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int main(int argc,char * argv[]){


  if( argc < 2){
    fprintf(stderr, "%s:ERROR: Require output file\n",argv[0]);
    exit(1);
  }

  char tmp_path[PATH_MAX];
  srand(time(NULL));
  snprintf(tmp_path,PATH_MAX,"/tmp/icc221-lab11-tmp.%08u",rand());

  FILE * tmp = fopen(tmp_path,"w");

  char buf[1024];
  int n;
  while( (n=read(0,buf,1024)) > 0){
    
    int i;
    for(i=0;i<n;i++,n--){
      char tmp = buf[i];
      buf[i] = buf[n-1];
      buf[n-1] = tmp;
    }
    fprintf(tmp,"%s",buf);
  }

  char cmd[PATH_MAX*3];
  snprintf(cmd,PATH_MAX*2,"/usr/bin/tac %s > %s",tmp_path,argv[1]);
  system(cmd);
  
  unlink(tmp_path);
  
  return 0;
}
