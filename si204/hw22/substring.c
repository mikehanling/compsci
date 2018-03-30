//Mike Hanling

#include <stdio.h>
#include <string.h>


char* is_in(char* target, char* test);


int main() {
  char tar[128];
  char test[128];

  printf("Target: ");
  scanf(" %s", tar);
  printf("Test: ");
  scanf(" %s", test);

  printf("%s\n", is_in(tar, test));

  return 0;
}  //end main


char* is_in(char* target, char* test) {
  int isin = -1;  //stays -1 if first letter of target is not in test

  //if target is longer than test, then no
  if (strlen(target) > strlen(test)) {
    return "no";
  }

  //for each letter in test
  for (int i = 0; i < strlen(test); i++) {
    //if this letter matches first letter of target
    if (test[i] == target[0]) {
      isin = 1;
      //check the subsequent letters of target against test
      for (int j = 0; j < strlen(target); j++) {
        if (test[i+j] != target[j]) {
          isin = 0;
        }
      }
      //if all match, then yes
      if (isin == 1) return "yes";
    }
  }

  //if all never matched, then no
  return "no";
}
