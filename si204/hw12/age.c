#include "si204.h"

int main() {
  cstring name;
  int month, day, year;

  fscanf(stdin, "%s %i/%i/%i", name, &month, &day, &year);

  int ans;
  ans = 2017-year;
  if (month > 2 || (month == 2 && day > 6)) {
    ans--;
  }

  fprintf(stdout, "%s is %i years old.\n", name, ans);

  return 0;
}
