#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define MAX_ARGS 128

/***************************************************************************************
 * babypipe.c
 *
 * Will unroll and execute the pipeline with pipe() and dup()
 *
 * USe thes MAKE options to test with different pipelines
 *  - make 0  : cat /etc/passwd | cut -d : -f 7 | sort | uniq 
 *  - make 1  : cat sample-db.csv | cut -d , -f 8 | sort | uniq | wc -l
 *  - make 2  : cat sample-db.csv | cut -d , -f 10 | cut -d - -f 1 | sort | uniq |wc -l
 *  - make 3  : cat | cut -d , -f 10 | cut -d - -f 1 | sort | uniq |wc -l 
 *  - make 4  : cat sample-db.csv | tail
 *  - make 5  : head sample-db.csv
 ****************************************************************************************/

int main(int argc, char * argv[]){


#ifndef PIPE
  // make
  // make 0
  // cat /etc/passwd | cut -d : -f 7 | sort | uniq ;
  char * pipeline[5][6] = {
    { "cat", "/etc/passwd", NULL},    
    { "cut", "-d", ":", "-f" , "7", NULL},
    { "sort", NULL},
    { "uniq", NULL},
    {NULL},
  };
#elif PIPE == 1
  // make 1
  // cat sample-db.csv | cut -d , -f 8 | sort | uniq | wc -l;
  char * pipeline[6][6] = {
    { "cat", "sample-db.csv", NULL},    
    { "cut", "-d", ",", "-f" , "8", NULL},
    { "sort", NULL},
    { "uniq", NULL},
    { "wc", "-l", NULL},
    {NULL},
  };
#elif PIPE == 2
  // make 2
  // cat sample-db.csv | cut -d , -f 10 | cut -d - -f 1 | sort | uniq |wc -l;
  char * pipeline[7][6] = {
    { "cat", "sample-db.csv", NULL},    
    { "cut", "-d", ",", "-f" , "10", NULL},
    { "cut", "-d", "-", "-f" , "1", NULL},
    { "sort", NULL},
    { "uniq", NULL},
    { "wc", "-l", NULL},
    {NULL},
  };
#elif PIPE == 3
  // make 3
  // cat | cut -d , -f 10 | cut -d - -f 1 | sort | uniq |wc -l;
  char * pipeline[7][6] = {
    { "cat", NULL},    
    { "cut", "-d", ",", "-f" , "10", NULL},
    { "cut", "-d", "-", "-f" , "1", NULL},
    { "sort", NULL},
    { "uniq", NULL},
    { "wc", "-l", NULL},
    {NULL}};
#elif PIPE == 4
  // make 4
  // cat smaple-db.csv | tail
  char * pipeline[3][4] = {
    { "cat", "sample-db.csv", NULL},    
    { "tail", NULL},
    {NULL}};
#elif PIPE == 5
  // make 5
  // head smaple-db.csv
  char * pipeline[2][3] = {
    { "head", "sample-db.csv", NULL},    
    {NULL}};
#else
  char * pipeline[1][1] = {{NULL}};
#endif


  pid_t cpid;
  int i, status;

  int cur_pipe[2];
  int last_pipe[2];

 
  //iterate through pipeline
  for(i=0; pipeline[i][0] != NULL; i++){
  
    //TODO: Setup the pipeline:
    //
    //   General outline:
    //     - create cur_pipe in parent
    //     - fork
    //       + child: duplicate read from last_pipe
    //       + child: duplicate write to cur_pipe
    //       + parent: shift cur_pipe to last pipe
    //       + parent: widow pipe by closing last_pipe[1]
    //    - Parent: wait for all children to close
    //
    //  Notes: 
    //   - Will hange if forget to widow pipe
    //   - Check for ends of pipeline. The front of the pipeline, doe
    //     not duplicate stdin The end of pipeline, do not duplicate stdout
    

  }  


  //wait for all children;
  while( wait(&status) > 0) ;
  
  return 0;
}
