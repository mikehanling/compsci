#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>

#define BUF_SIZE 1024
int main(){

  int i;
  pid_t pid;
  char path[PATH_MAX],dest[PATH_MAX];
  char cmd1[PATH_MAX*3],cmd2[PATH_MAX*2];
  char tmp_path[PATH_MAX];
  char b;

  pid=getpid();

  sprintf(path, "/proc/%d/exe",pid);
  if (readlink(path, dest, PATH_MAX) == -1){
    perror("readlink");
    exit(1);
  }


  for(i=strlen(dest);dest[i]!='/';i--);
  dest[i]='\0';
  strncat(dest,"/secret ",PATH_MAX);
 

  srand(time(NULL));

  snprintf(tmp_path,PATH_MAX,"/tmp/icc221-lab11-tmp.%08u",rand());

  snprintf(cmd1,PATH_MAX*3,"cat %s > %s",dest,tmp_path); 

  system(cmd1);

  snprintf(cmd2,PATH_MAX*2,"sha1sum %s",tmp_path);
  system(cmd2);

  unlink(tmp_path);
}
