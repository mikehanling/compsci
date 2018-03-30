//Mike Hanling
//202430
//
//Lab 04 - Part 22 EC
//Discussed with Chris Daves

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(time(NULL));
  for (int i = 0; i < 16; i++) {
    printf("%d", rand() % 10);
  }
  printf("\n");
  return 0;
}
