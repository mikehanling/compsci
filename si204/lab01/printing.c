#include "si204.h"

int main() {
  fputs("And then my heart with pleasure fills,\n", stdout);
  fputs("And dances with the daffodils.\n\n", stdout);
  fputs("And then my heart with pleasure fills,\n", stdout);
  fputs("And whistles with the daffodils.\n\n", stdout);
  fputs("And then my heart with pleasure fills,\n", stdout);
  fputs("And sits down with the daffodils.\n\n", stdout);
  fputs("And then my heart with pleasure fills,\n", stdout);
  fputs("And listens to the daffodils.\n\n", stdout);
  int num = 1;
  fputs("I like ", stdout);
  writenum(num, stdout);
  num += 1;
  fputs(" flower.\n", stdout);
  fputs("I like ", stdout);
  writenum(num, stdout);
  num += 1;
  fputs(" flowers.\n", stdout);
  fputs("I like ", stdout);
  writenum(num, stdout);
  num += 1;
  fputs(" flowers.\n", stdout);
  fputs("I like ", stdout);
  writenum(num, stdout);
  num += 1;
  fputs(" flowers.\n", stdout);
  fputs("I like ", stdout);
  writenum(num, stdout);
  num += 1;
  fputs(" flowers.\n", stdout);
  fputs("\n", stdout);
  fputs("And then my heart with pleasure fills, and dances with the daffodils.", stdout);


  return 0;
}
