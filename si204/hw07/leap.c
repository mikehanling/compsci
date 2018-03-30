#include "si204.h"

int main() {
  int again = 1;
  while (again == 1) {
    fputs("What is your favorite leap year? ", stdout);
    int year = readnum(stdin);
    if (year%4 == 0 && year%100 == 0) {
      if (year%400 == 0) {
        fputs("Yes, ", stdout);
        writenum(year, stdout);
        fputs(" was a good year.", stdout);
        again += 1;
      }else {
        writenum(year, stdout);
        fputs(" is not a leap year!\n", stdout);
      }
    }else if (year%4 == 0) {
      fputs("Yes, ", stdout);
      writenum(year, stdout);
      fputs(" was a good year.", stdout);
      again += 1;
    }else {
      writenum(year, stdout);
      fputs(" is not a leap year!\n", stdout);
    }
  }
          

  return 0;
}
