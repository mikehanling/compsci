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

/************************************************************
 * sleep-unroll.c
 *
 * Unroll a pipeline of sleep calls, placing all children in their own
 * process group. 
 *
 * Sample Usage:
 *  $ ./sleep_unroll "sleep 1"   
 *  $ ./sleep_unroll "sleep 1 | sleep 2"
 *  $ ./sleep_unrill "sleep 2 | sleep 3 | sleep 1"
 *
 ************************************************************/


int main(int argc, char * argv[]){

  pid_t cpid;
  pid_t cpgid=0; 

  int i, status;
  char * cmd_argv[MAX_ARGS];
  char * line, * tok;
   
  //split the command based on | into lines
  line = strtok(argv[1], "|");
  do{
    
    cpid = fork();

    //child
    if( cpid == 0 ) {

      //set cpgid to the pid of the first child
      if (cpgid == 0)
        cpgid = getpid();

      //set pgid to the first child's pid=pgid
      setpgid(0, cpgid);

      //tokenize the command
      i = 0;
      tok = strtok(line, " ");
      cmd_argv[i] = strdup(tok);

      while ( (tok = strtok(NULL, " ")) != NULL) {
        i++;
        if (i < MAX_ARGS)
          cmd_argv[i] = strdup(tok);
      }
      cmd_argv[i+1] = NULL;   //NULL terminate the array
      for (int i = 0; i < 3; i++) {
      }

      //exec the command
      execvp(cmd_argv[0], cmd_argv);
      perror(cmd_argv[0]);
      return 1;

    //parent
    }else if ( cpid > 0 ) {

      if (cpgid == 0)
        cpgid = cpid;
      setpgid(cpid, cpgid);


    }else{
      perror("fork");
      return 2;
    }
    
    //
    //   General outline:
    //    (fork)
    //      + Child: setpgid of itself
    //      + Child: parse command and exec
    //      + Parent: setpgid of child
    //
    //   Notes:
    //     - All children should be in the same process group
    //     - Use the pid of the *first* child as the pgid
    //     - Take advantage of setpgid(cpid,0) and setpgid(0,0)
    //       properties to assist logic
    //     - You can create orphaned process groups, be sure to kill
    //     - those with killall
    

  }while( (line = strtok(NULL, "|")) != NULL);

  //wait for all children in a process group
  while(waitpid(-cpgid, &status, 0) > 0); //DO NOT EDIT
	 
  //SUCCESS!
  return 0;
}
