//Mike Hanling

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int rolldie();


int main() {
  int seed = 0;  //the default for this program instead of C default
  
  //user input and assignment
  printf("Enter seed value: ");
  if (scanf(" %i", &seed) != 1) {
    exit(1);
  }
  srand(seed);

  //simulates 5 rolls
  for (int i = 0; i < 5; i++) {
    int roll1 = rolldie();
    int roll2 = rolldie();
    int sum = roll1 + roll2;

    printf("Player rolled %i + %i = %i\n", roll1, roll2, sum);
  }

  return 0;
}

int rolldie() {
  //returns random int between 1 and 6, inclusive
  while (1) {
    int randnum = 1 + rand()%8;
    if (randnum <= 6) return randnum;
  }
}

