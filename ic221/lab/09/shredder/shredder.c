#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/wait.h>
#include <sys/types.h>

int ticks = 0;
pid_t cpid;

void tick(int signum){
  //TODO: complete the SIGALRM handler
  //
  // One each alarm, print 
  //    printf("%d: tick-tock\n", ticks);
  //
  // If 5 ticks occur, kill the child with SIGKILL
  //
  // (hint: don't forget to set the next alarm)
  printf("%d: tick-tock\n", ++ticks);


  if (ticks < 5)
    alarm(1);
  else
    kill(cpid, SIGKILL);

  signal(SIGALRM, tick);
}

int main(int argc, char * argv[]){


  int status = 0;

  if (( cpid = fork()) == 0){
    /*CHILD*/

    execvp(argv[1], argv+1);
    perror("execvp");
    _exit(1);
  }else if ( cpid > 0){
    /*PARENT*/

    signal(SIGALRM, tick);

    alarm(1);
  
    wait(&status);

    if (ticks < 3) {
      printf("Blast that grotesque ganglion! You let them get away!\n");
    }else if (ticks < 5) {
      printf("Sayonara you shell-backed simpletons. I'll get you next time!\n");
    }else {
      printf("Tonight I dine on turtle soup! Muhaha!\n");
    }

    //TODO: Complete the program
    // 
    // If the child finished before 3 ticks:
    //  "Blast that grotesque ganglion! You let them get away!\n"
    //
    // If the child finished after 3 ticks but not killed:
    //  "Sayonara you shell-backed simpletons. I'll get you next time!\n"
    //
    // If the child was killed:
    //  "Tonight I dine on turtle soup! Muhaha!\n"
    //
    // (hint: don't forget to turn off unscheduled alarms)
    // (hint: recall the WIF---() functions ...)

    
  }else{
    /*ERROR*/
    perror("fork");
    _exit(1);
  }

  return 0;
}
