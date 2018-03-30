//Mike Hanling


#include "si204.h"


int main() {
  int deadhour = 0;
  int deadmin = 0;
  int currhour = 0;
  int currmin = 0;
  int timeleft = 0;
  cstring trash;
  char when;
  char garb;

  
  printf("Deadline: ");
  scanf(" %i:%i", &deadhour, &deadmin);
  
  printf("Current time: ");
  scanf(" %i%c", &currhour, &garb);
  if (garb == ':') {
    scanf("%i%c%c", &currmin, &when, &garb);
  }else {
    when = garb;
    scanf("%c", &garb);
  }


  if (when == 'p') {
    currhour += 12;
  }else if (currhour == 12) {
    currhour = 0;
  }

  if (currhour > deadhour || (currhour == deadhour && currmin > deadmin)) {
    printf("Too late!\n");
  } else {
    timeleft += (deadhour - currhour)*60;
    timeleft += deadmin - currmin;
    printf("You have %i minutes remaining\n", timeleft);
  }

  return 0;
}
