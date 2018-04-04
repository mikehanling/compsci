#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <libgen.h>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/signal.h>

#define MAX_ARGS 128

void ignore(int signum) {}



int main(int argc, char * argv[]){


  char * line;    //DO NOT EDIT, for readline
  char prompt[256];    //DO NOT EDIT, for readline
  char * tok;   //NOTE: This is useful for tokenizatoin
  char * cmd;

  char * commands[64];       //NOTE: can only handle up to 63 pipes
  char * cmd_argv[MAX_ARGS]; //NOTE: use this store your argv array, 
                             //      don't go beyond MAX_ARGS
                             
  pid_t cpid; //NOTE: to store child pid
  pid_t cpgid = 0;
  pid_t bg_pgid = -1;
  int status, i, index = 0; //NOTE: For wait status and iteration
  
  int cur_pipe[2];
  int last_pipe[2] = {-1, -1};
  int stdin_cp = dup(0);
  int stdout_cp =dup(1);

  //register what to do for SIGTTOU
  signal(SIGTTOU, ignore);

  //for readline setup, don't edit!
  rl_bind_key('\t', rl_abort);

  while(1){
    
    tcsetpgrp(0, getpid());
    printf("1\n");
    //prompt
    char cwd[128];

    getcwd(cwd,128); //get the current working directory

    sprintf(prompt,              //store result of formating in string prompt
            "nvysh (%d): %s $ ", //the format string 
            bg_pgid,             //the process group id of the background process
            basename(cwd));      //the basename of the current working directory

    printf("2\n");
    //readline allocates a new line every time it reads
    line = readline(prompt); 
    
    printf("3\n");
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

    //check for fg
    if (strcmp(line, "fg") == 0) {
      kill(-bg_pgid, SIGCONT);
      tcsetpgrp(0, bg_pgid);
      bg_pgid = -1;
      continue;
    }
    printf("After fg check\n");

    //split the command based on | into cmds
    i = 0;
    cmd = strtok(line, "|");
    commands[i] = strdup(cmd);
    while ( (cmd = strtok(NULL, "|")) != NULL) {
      i++;
      if (i < MAX_ARGS)
        commands[i] = strdup(cmd);
    }
    free(line);
    commands[i+1] = NULL;

    printf("After split, before do\n");

    //for each cmd...
    do {

      //open pipe
      if (pipe(cur_pipe) < 0) {
        perror("pipe");
        _exit(1);
      }

      //fork
      cpid = fork();

      //child
      if (cpid == 0) {

        //  ID WORK

        //set cpgid to the pid of the first child
        if (cpgid == 0)
          cpgid = getpid();

        //set pgid to the first child's pid=pgid
        setpgid(0, cpgid);


        //  TOKEN WORK

        //Tokenize the cmd to construct a argv array
        i = 0;
        tok = strtok(commands[index], " ");
        cmd_argv[i] = strdup(tok);

        while ( (tok = strtok(NULL, " ")) != NULL) {
          i++;
          if (i < MAX_ARGS)
            cmd_argv[i] = strdup(tok);
        }
        free(tok);
        cmd_argv[i+1] = NULL;   //NULL terminate the array
        
        //get for fg
        if (strcmp(cmd_argv[0], "fg") == 0 && cmd_argv[1] == NULL) {
          kill(bg_pgid, SIGCONT);
          bg_pgid = -1;
          wait(&status);
          continue;
        }


        //  PIPE WORK

        //if first, close read end of pipe and map stdout to pipe
        if (last_pipe[0] == -1) {
          close(cur_pipe[0]);

          //as long as this is not a one command job...
          if (commands[index + 1] != NULL) {
            close(1);
            dup2(cur_pipe[1], 1);
          }

        //if last, map stdin to pipe and close write end of pipe
        }else if (commands[index+1] == NULL) {
          close(last_pipe[1]);
          close(cur_pipe[1]);
          close(0);
          dup2(last_pipe[0], 0);
        
        //if any other, map stdin and stdout to pipe
        }else{
          close(last_pipe[1]);
          close(0);
          dup2(last_pipe[0], 0);
          close(cur_pipe[0]);
          close(1);
          dup2(cur_pipe[1], 1);
        }
        

        //  EXEC WORK

        //run cmd
        execvp(cmd_argv[0], cmd_argv);

        //if it throws error, handle it
        perror("./nvysh");
        return 2;


      }else if (cpid > 0) {
      //parent
        
        //eliminate race condition
        if (cpgid == 0)
          cpgid = cpid;
        setpgid(cpid, cpgid);
        
        //wait and change pipes over
        last_pipe[0] = cur_pipe[0];
        last_pipe[1] = cur_pipe[1];
        close(last_pipe[1]);

      }else {
      //fork error
        perror("fork");
        return 1;
      }
      
    }while( commands[++index] != NULL );

    //set the fg process for terminal control
    tcsetpgrp(0, cpgid);

    //wait for all children in a process group
    while(waitpid(-cpgid, &status, WUNTRACED) > 0) {
      if (WIFSTOPPED(status) && bg_pgid == -1) {
        tcsetpgrp(0, getpid());
        kill(-cpgid, SIGSTOP);
        kill(getpid(), SIGCONT);
        bg_pgid = cpgid;
        break;
      }
    }

    printf("After the waitpid\n");
    //reset variables for next prompt
    cpgid = 0;
    dup2(stdin_cp, 0);
    dup2(stdout_cp, 1);
    index = 0;

    //reset nvysh as the fg process for terminal control
    //tcsetpgrp(0, getpid());
    printf("Last command\n");
  }

  return 0;
}
