#include "si204.h"

int main() {
  fputs("Enter a 4-bit binary number: ", stdout);
  char cone = readchar(stdin);
  char ctwo = readchar(stdin);
  char cthree = readchar(stdin);
  char cfour = readchar(stdin);
  
  int dec = 0;

  dec += 8*(((int)cone)-48);
  dec += 4*(((int)ctwo)-48);
  dec += 2*(((int)cthree)-48);
  dec += 1*(((int)cfour)-48);

  fputs("In decimal ", stdout);
  fputc(cone, stdout);
  fputc(ctwo, stdout);
  fputc(cthree, stdout);
  fputc(cfour, stdout);
  fputs(" = ", stdout);  
  writenum(dec, stdout);


  return 0;
}
