#include "si204.h"

int main() {
  fputs("Time: ", stdout);
  int time = readnum(stdin);
  if (time >= 600 && time <= 2300) {
    fputs("Awake", stdout);
  }
  else {
    fputs("Asleep", stdout);
  };


  return 0;
}
