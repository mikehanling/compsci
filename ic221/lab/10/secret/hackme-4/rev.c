#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <fcntl.h>

int main(int argc,char * argv[]){


  if( argc < 2){
    fprintf(stderr, "%s: ERROR: Require input file\n",argv[0]);
    exit(1);
  }

  int fd;

  if((fd= open(argv[1],O_RDONLY)) < 0){
    fprintf(stderr, "%s: ERROR: Cannot open input file '%s'\n",argv[0],argv[1]);
    exit(1);
  }

  char buf[1024];
  int n;
  while( (n=read(fd,buf,1024)) > 0){
    
    int i;
    for(i=0;i<n-1;i++,n--){
      char tmp = buf[i];
      buf[i] = buf[n-2];
      buf[n-2] = tmp;
    }
    printf("%s",buf);
  }

}
