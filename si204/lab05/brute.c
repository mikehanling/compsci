//Mike Hanling
//DID NOT FINISH
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rolldie();
int throwdice();
int play(int seed);


int main() {
  printf("Enter max: ");
  int max = 0;
  scanf(" %i", &max);
  int wins = 0;
  int gold = 0;

  for (int i = 0; i < max; i++) {
    int winspos = play(i);
    int winsneg = play(-i);
    if (winspos > wins) {
      wins = winspos;
      gold = i;
    }else if (winsneg > wins) {
      wins = winsneg;
      gold = -i;
    }
  } 

  printf("Best seed value: %i", gold);

  return 0;
}


int play(int seed) {
  srand(seed);
  
  //simulate throws until winner
  int cplay = 0;
  int setpoint = 1;  //this value is not possible in a two-dice roll
  int wins = 0;
  char yesno = 'y'; //default is to keep the game going
  do {
    cplay = throwdice(setpoint);

    if (cplay == 0) {
      wins += 1;
      setpoint = 1;  //rest for next game
    }else if (cplay == -1) {
      return wins;
    }
    if (setpoint == 1) {  //if the first throw is over
      setpoint = cplay;
    }
  } while (yesno == 'y');  //will only be wrong if game has finished and user says no

}


int rolldie() {
  //returns a random int between 1 and 6, inclusive
  while (1) {
    int randnum = 1 + rand()%8;
    if (randnum <= 6) return randnum;
  }
}


int throwdice(int setpoint) {
  //get two rolls
  int die1 = rolldie();
  int die2 = rolldie();
  int tot = die1 + die2;

  //evaluates first throw of the dice
  if (setpoint == 1) {  
    if (tot == 7 || tot == 11) {
      //printf("Player rolled %i + %i = %i Player wins!\n", die1, die2, tot);
      return 0;
    }else if (tot == 2 || tot == 3 || tot == 12) {
      //printf("Player rolled %i + %i = %i House wins!\n", die1, die2, tot);
      return -1;
    }else {
      //printf("Player rolled %i + %i = %i roll again\n", die1, die2, tot);
      return tot;
    }
  }else {  //evaluates all subsequent rolls
    if (tot == setpoint) {
      //printf("Player rolled %i + %i = %i Player wins!\n", die1, die2, tot);
      return 0;
    }else if (tot == 7) {
      //printf("Player rolled %i + %i = %i House wins!\n", die1, die2, tot);
      return -1;
    }else {
      //printf("Player rolled %i + %i = %i roll again\n", die1, die2, tot);
      return tot;
    }
  }

}
