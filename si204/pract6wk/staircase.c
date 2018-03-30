//Mike Hanling

#include "si204.h"

int main() {
  printf("Enter words: ");
  cstring current;
  int another = 1;
  int longlength = 0;
  int currlength = 0;

  while (another) {
    scanf(" %s", current);
    currlength = strlen(current);
    printf("%s\n", current);
    for (int i = 0; i < longlength; i++) {
      printf(".");
    }
    for (int j = 0; j < currlength; j++) {
      printf("#");
    }
    longlength += currlength;
    if (strcmp(current, "bye") == 0) {
      another = 0;
      printf("\n");
    }
  }



  return 0;
}
