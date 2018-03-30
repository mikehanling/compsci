#include "si204.h"

int main() {
  cstring item;
  readstring(item, stdin);
  double price = readnum(stdin);
  int quant = readnum(stdin);
  writenum(quant, stdout);
  fputs(" ",stdout);
  fputs(item, stdout);
  fputs(" cost $", stdout);
  writenum(price * quant, stdout);
  fputs("\n", stdout);

  return 0;
}
