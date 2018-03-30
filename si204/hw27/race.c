//Mike Hanling


#include <stdio.h>


typedef struct{
  char name[128];
  double time;
} racer;


racer bettertime(racer one, racer two);

  
int main() {
  printf("Enter the names and times of two racers:\n");
  racer one;
  scanf(" %s %lg", one.name, &one.time);
  racer two;
  scanf(" %s %lg", two.name, &two.time);

  racer winner = bettertime(one, two);

  printf("%s won with a time of %g minutes.\n", winner.name, winner.time);

  return 0;
}


racer bettertime(racer one, racer two) {
  if (one.time < two.time) {
    return one;
  }
  return two;
}
