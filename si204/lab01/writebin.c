#include "si204.h"

int main() {
  fputs("Enter a number between 0 and 15: ", stdout);
  int num = readnum(stdin);
  int out = num;
  char c4 = (num%2)+48;
  num /=2;
  char c3 = (num%2)+48;
  num /= 2;
  char c2 = (num%2)+48;
  num /= 2;
  char c1 = (num%2)+48;
  

  writenum(out, stdout);
  fputs(" in binary is ", stdout);
  fputc(c1, stdout);
  fputc(c2, stdout);
  fputc(c3, stdout);
  fputc(c4, stdout);

  return 0;
}
