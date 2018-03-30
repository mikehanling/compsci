//Mike Hanling
//pangram.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int search(char* data, int size, char x);
int match(char a, char b);

int main() {
  int total = 0;
  int count = 0;
  char* lettersin = calloc(26, sizeof(char));

  while(count < 26) {
    char curr[32];
    scanf(" %s", curr);

    for (int i = 0; i < strlen(curr); i++) {
      if (count == 0) {
        lettersin[count] = curr[i];
        count++;
      }else if (search(lettersin, count, curr[i]) == count) {
        lettersin[count] = curr[i];
        count++;
      }
    }

    total += strlen(curr);
  }

  printf("%i letters\n", total);

  free(lettersin);

  return 0;
}

int search(char* data, int size, char x) {
  int i = 0;
  while(i < size && !match(data[i], x)) {
    i++;
  }
  return i;
}

int match(char a, char b) {
  return a == b;
}

