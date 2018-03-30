#include "si204.h"

int main () {
  fputs("Enter n: ", stdout);
  int in = readnum(stdin);
  int top = in;
  int sum = 0;
  
  while (top > 0) {
    sum += top;
    --top;
  };
  fputs("The sum of numbers from 1 up to ", stdout);
  writenum(in, stdout);
  fputs(" is ", stdout);
  writenum(sum, stdout);

  return 0;
}
