//Mike Hanling

#include "si204.h"

int main() {
  FILE* fin = fopen("secret.txt", "r");

  int correct = 0;
  fscanf(fin, " %i", &correct);
  
  int wrong = 1;
  int guess = 0;
  int tab = 0;

  while (wrong) {
    printf("Next guess: ");
    scanf(" %i", &guess);
    if (guess == correct) {
      tab += 5;
      wrong = 0;
    }else {
      tab -= 1;
    }
  }

  if (tab < 0) {
    printf("You lost $%i", tab*-1);
  }else {
    printf("You won $%i", tab);
  }

  return 0;
}
