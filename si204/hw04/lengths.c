#include "si204.h"
#include <math.h>

int main() {
  fputs("Enter two lengths in feet and inches (larger first!)\n", stdout);
  int feet1 = readnum(stdin);
  char c = readchar(stdin);
  int inch1 = readnum(stdin);
  c = readchar(stdin);
  int feet2 = readnum(stdin);
  c = readchar(stdin);
  int inch2 = readnum(stdin);
  int length1 = feet1*12 + inch1;
  int length2 = feet2*12 + inch2;
  int diff = length1 - length2;
  int feet = diff/12;
  int inch = diff%12;
  fputs("Difference is ", stdout);
  writenum(feet, stdout);
  fputs("' ", stdout);
  writenum(inch, stdout);
  fputs("\"", stdout);
  
  
  return 0;
}
