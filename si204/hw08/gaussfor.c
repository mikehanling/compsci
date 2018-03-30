#include "si204.h"

int main() {
  fputs("Enter n: ", stdout);
  int n = readnum(stdin);
  fputs("The sum of numbers from 1 up to ", stdout);
  writenum(n, stdout);
  fputs(" is ", stdout);
  int ans = 0;
  for(int i = n; i > 0; --i) {
    ans += i;
  }
  writenum(ans, stdout);


  return 0;
}
