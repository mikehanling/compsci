#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

#define MAX_ARGS 128

int timeval_subtract (struct timeval *result, struct timeval *x, struct timeval *y) {
  /* Perform the carry for the later subtraction by updating y. */
  if (x->tv_usec < y->tv_usec) {
    int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
    y->tv_usec -= 1000000 * nsec;
    y->tv_sec += nsec;
  }
  if (x->tv_usec - y->tv_usec > 1000000) {
    int nsec = (x->tv_usec - y->tv_usec) / 1000000;
    y->tv_usec += 1000000 * nsec;
    y->tv_sec -= nsec;
  }
     
  /* Compute the time remaining to wait.
     tv_usec is certainly positive. */
  result->tv_sec = x->tv_sec - y->tv_sec;
  result->tv_usec = x->tv_usec - y->tv_usec;
     
  /* Return 1 if result is negative. */
  return x->tv_sec < y->tv_sec;
}


int main(int argc, char * argv[]){


  char * line;    //DO NOT EDIT, for readline
  char prompt[256];    //DO NOT EDIT, for readline



  pid_t c_pid; //NOTE: to store child pid
  int status, i; //NOTE: For wait status and iteration
  
  char * cmd_argv[MAX_ARGS]; //NOTE: use this store your argv array, 
                             //      don't go beyond MAX_ARGS

  char * tok;   //NOTE: This is useful for tokenizatoin

  struct timeval start, end, diff; //for timing

  start.tv_sec = 0;
  start.tv_usec = 0;
  diff = end = start; //initialize times to zero
  
  //for readline setup, don't edit!
  rl_bind_key('\t', rl_abort);

  while(1){
    
    //prompt
    snprintf(prompt, 256, "mini-sh (%ld.%04ld) #> ", diff.tv_sec, diff.tv_usec/1000);

    //readline allocates a new line every time it reads
    line = readline(prompt); 
    
    //read EOF, break the loop
    if (line == NULL){
      printf("\n");
      break;
    }

    //read empty line, continue
    if (strcmp(line,"")==0){
      free(line);
      continue;
    }

    //TODO: Tokenize the line to construct a argv array
    i = 0;
    tok = strtok(line, " ");
    cmd_argv[i] = strdup(tok);

    while ( (tok = strtok(NULL, " ")) != NULL) {
      i++;
      if (i < MAX_ARGS)
        cmd_argv[i] = strdup(tok);
    }
    cmd_argv[i+1] = NULL;   //NULL terminate the array

    //TODO: Fork-Exec-Wait the command, and compute the time of execution
    //      store the time of execution in diff so that it will be 
    //      available in the next prompt.

    //fork
    c_pid = fork();

    //child
    if (c_pid == 0) {
      //run extra command
      execvp(cmd_argv[0], cmd_argv);

      //if it throws error, handle it
      perror("./mini-sh");
      return 2;

    }else if (c_pid > 0) {
    //parent
      
      //time before
      gettimeofday(&start, NULL);

      //wait till child finishes command
      wait(&status);

      //time after
      gettimeofday(&end, NULL);

      //get difference in time
      timeval_subtract(&diff, &end, &start);

    }else {
    //fork error
      perror("fork");
      return 1;
    }
      
    //HINT: Make sure you *always& exit in the child, in case exec
    //      fails. This could cause a fork bomb

    free(line); //free the current line, otherwise memleak
  }

  return 0;
}
