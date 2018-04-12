#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

int main(int argc, char * argv[]){

  char * USAGE = "%s [last-n]\n"; //USAGE string
  int last = 1; //how many last lines to read, default 1
  FILE * f_log; //open file

  //TODONE: update to your HOME directory
  char * path = "/home/mids/m202430/ic221-lab10-log.txt";


  if (argc >= 2){

    if(strcmp(argv[1],"-h") == 0){
      printf(USAGE,argv[0]);
      exit(1);
    }

    if (sscanf(argv[1],"%d",&last) == 0){
      fprintf(stderr, "ERROR: invalid value '%s'\n",argv[1]);
      fprintf(stderr,USAGE,argv[0]);
      exit(1);
    }
    

  }
  

  if( (f_log = fopen(path, "r")) == NULL){
    perror("fopen");
    fprintf(stderr, "ERROR: Opening Log File '%s'\n",path);
    exit(1);
  }

  //Check for an empty file
  fseek(f_log,0,SEEK_END);
  if(ftell(f_log) == 0) return 0;


  //TODONE: Read the last n-lines of the file
  //
  //  Algorithm big idea: You're tracking backwards in the file
  //  searching for newline symbols. Once you've found n newlines, you
  //  print out the file from that point to the end.

  char c;
  fseek(f_log, -1, SEEK_CUR);
  if (last < 0) {
    fprintf(stderr, "Invalid value '%d'\n", last);
    exit(2);
  }

  //read in backward and keep track of number of new lines
  while (last >= 0) {
    c = getc(f_log);
    if (c == '\n') last--;
    fseek(f_log, -2, SEEK_CUR);
    if (ftell(f_log) == 1) {
      fseek(f_log, -1, SEEK_CUR);
      break;
    }
  }

  //print character by character from here to the end of the file
  fseek(f_log, 2, SEEK_CUR);
  while (fscanf(f_log, "%c", &c) == 1) {
    printf("%c", c);
  }

  return 0;
}

