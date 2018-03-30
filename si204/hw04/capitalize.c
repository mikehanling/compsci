#include "si204.h"
#include <math.h>

int main() {
  fputs("Input word : ", stdout);
  char c1 = readchar(stdin);
  char c2 = readchar(stdin);
  char c3 = readchar(stdin);
  c1 -= 32;
  fputs("Capitalized: ", stdout);
  fputc(c1, stdout);
  fputc(c2, stdout);
  fputc(c3, stdout);

  return 0;
}
