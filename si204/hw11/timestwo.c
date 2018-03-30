#include "si204.h"

int main() {
  fputs("Enter n: ", stdout);
  int factor = readnum(stdin);
  fprintf(stdout, "2 * %i = %i.", factor, factor*2);


  return 0;
}
