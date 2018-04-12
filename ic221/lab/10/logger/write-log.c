#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>

//TODONE: Compile and set up to run as set-bit for the user

int main(int argc, char * argv[]){

  char * USAGE = "%s log-info\n";
  FILE * f_log;

  //TODONE: update to your HOME directory
  char * path = "/home/mids/m202430/ic221-lab10-log.txt";


  if (argc < 2){
    fprintf(stderr, "ERROR: require log-info\n");
    fprintf(stderr, USAGE, argv[0]); 
    exit(1);
  }


  if(strcmp(argv[1],"CLEAR") == 0){

    //TODONE: Check to make sure only the owner (not the set-user-id)
    //user can clear the file!
    if (getuid() != geteuid()) {
      fprintf(stderr, "ERROR: Unauthorized user attempting to clear the log file");
      exit(2);
    }

    //truncate the file if the form is to clear
    if( (f_log = fopen(path, "w")) == NULL){
      perror("fopen");
      fprintf(stderr, "ERROR: Cannot open log-file at '%s'\n",path);
      exit(1);
    }
    fclose(f_log);
    return 0;
  }

  //open for append
  if( (f_log = fopen(path, "a")) == NULL){
    perror("fopen");
    fprintf(stderr, "ERROR: Cannot open log-file at '%s'\n",path);
    exit(1);
  }

  //compute a timestamp
  time_t t;
  time(&t);
  char * s = ctime(&t);
  s[strlen(s)-1] = '\0';

  //write to the log
  fprintf(f_log, "[%s] (%d) %s\n",s,getuid(),argv[1]);

  //close the log file
  fclose(f_log);

  return 0;
}
