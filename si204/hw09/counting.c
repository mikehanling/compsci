#include "si204.h"

int main() {
  fputs("Enter n: ", stdout);
  int top = readnum(stdin);
  for (int i = 0; i < top; i++) {
    for (int j = 1; j < i+2; j++) {
      writenum(j, stdout);
      if (j < i+1) {
        fputc(' ', stdout);
      }
    }
    fputc('\n', stdout);
  }


  return 0;
}
