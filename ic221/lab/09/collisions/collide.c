#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "myhashlib.h"


//How many child process to use: You can change this to lower values
//if you want to do some testing. One is a good choice to start with.
#define NUM_WORKERS 4

//The first (ASCII_START) and last (ASCII_END-1) printable
//ASCII values
#define ASCII_START 33
#define ASCII_END 127


//Store all the pipes here
int pipes[NUM_WORKERS][2];

//Store all the pid's here
pid_t workers[NUM_WORKERS];


//Routine for trying all the passwords
//DO NOT EDIT
void crack(char *hash, char *guess, int index,int fd){
  if(index == MSG_LEN){

    char collision[HASH_LEN];
    myhash(guess,MSG_LEN,collision);
    if(strcmp(hash,collision) == 0){
      //found a match!

      //signal parent and write to the password to the pipe
      write(fd, guess, MSG_LEN);
      kill(getppid(),SIGUSR1); 
    }
    return;
  }

  char c;
  for(c=ASCII_START; c < ASCII_END ; c++){
    guess[index] = c;
    crack(hash,guess,index+1,fd);
  }
  
  return ;
}

//Worker/Child Proces routine
//DO NOT EDIT
int do_work(int pipe_fd[]){

  char hash[HASH_LEN];


  //get the hash from the parent by reading the pipe
  read(pipe_fd[0], hash, HASH_LEN);
  
  while(1){
    
    //read the first letter of passwords to check
    char start;
    if( read(pipe_fd[0], &start, 1) < 0 ) break;
    if(start == 0) break;

    char guess[MSG_LEN]={0};
    guess[0] = start;

    //crack the password
    crack(hash,guess,1,pipe_fd[1]);

    //stop, which will signal the parent, the wait to be continue to
    //read the next letter or be killed.
    raise(SIGSTOP);
  }
  
  return 1;
}

//Routine to kill all the workers
//DO NOT EDIT
void cleanup(){
  int i;
  for(i=0;i<NUM_WORKERS;i++)
    kill(workers[i],SIGKILL);

}

void read_child(int signum, siginfo_t * info, void * context) {
  for (int i = 0; i < NUM_WORKERS; i++) {
    if (info->si_pid == workers[i]) {
      char* c[1];
      read(pipes[i][0], c, 1);
      write(1, c, 1);
    }
  }

  
}

  

int main(int argc, char * argv[]){
  //int stdin_copy = dup(0);
  //int stdout_copy = dup(1);

  if(argc < 2){
    fprintf(stderr, "ERROR: require hash\n");
    exit(1);
  }

  if(strlen(argv[1]) != HASH_LEN-1){
    fprintf(stderr, "ERROR: hash length incorrect: must be %d long\n",HASH_LEN-1);
    exit(1);
  }

  //cleanup all the workers in case of exit
  //so you don't have zombies or orphans
  atexit(cleanup);

  //TODO:
  //
  // (1) Establish a sigaction signal handler for SIGUSR1 with
  //     sigaction() so that every time you find a collision you can
  //     print it out by reading from that child's pipe.
  //
  // (2) Fork the child processes with a pipe to each, saving the
  //     information in wokers and pipes.
  //
  //     For each child:
  //
  //     a. write the hash they should crack to the pipe
  //
  //     b. write the first letter of the password they are to start
  //        cracking with
  //
  // (3) Monitor childrens state with waitpid(): if a child stops, and
  //     there are more first letters to start with, communicate that
  //     and continue the child, if not kill the child.
  //
  // (4) When there are no more children alive exit the program.

  struct sigaction action;
  action.sa_sigaction = read_child;
  action.sa_flags = SA_SIGINFO;
  sigaction(SIGUSR1, &action, NULL);

  char c;
  pid_t ppid = getpid();
  int index = 0;
  for(int i = 0; i < NUM_WORKERS; i++) {
    if (pipe(pipes[i]) < 0) {
      perror("pipe");
      return 1;
    }

    write(pipes[i][1], argv[1], strlen(argv[1]));
    c = ASCII_START + index;
    index++;
    write(pipes[i][1], &c, 1);

    workers[i] = fork();

    if (workers[i] == 0)
      do_work(pipes[i]);

  }
  
  if (ppid == getpid()) {
    int status;
    pid_t cpid;
    while ((cpid = waitpid(0, &status, WUNTRACED)) != 1) {

      int currchild = 0;
      for (int i = 0; i < NUM_WORKERS; i++) {
        if (getpid() == workers[i]) break;
      }
      
      if (WIFSTOPPED(status)) {
        if ((ASCII_START + index) <= ASCII_END) {
          c = ASCII_START + index;
          index++;
          write(pipes[currchild][1], &c, 1);
          kill(SIGCONT, cpid);
        }else
          kill(cpid, 9);
      }
    }
  }
    

  return 0;
}
