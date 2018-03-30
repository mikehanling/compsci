//Mike Hanling

#include <stdio.h>
#include <string.h>

//Prototype
void split(double total, int* dollars, int* cents);

int main() {
  printf("Enter amount: ");
  fflush(stdout);

  double amt;
  if (scanf(" $%lg", &amt) != 1) {
    printf("ERROR: must enter something like $3.50\n");
    return 1;
  }

  // FUNCTION CALL HERE!
  int dollars;
  int cents;
  split(amt, &dollars, &cents);

  printf("That's %i dollars and %i cents.\n", dollars, cents);

  return 0;
}

//Definition
void split(double total, int* dollars, int* cents) {
  *dollars = total;  //will take only dollar part bc of type
  *cents = (total - *dollars)*100;  //takes remaining cents
}
