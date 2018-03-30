//Mike Hanling

#include <stdio.h>

void countdown(int n) {

  //Base cases
  if (n == 0) {
    printf("hooray!\n");
    return;
  }
  
  // Normal Case
  printf("%i\n", n);
  countdown(n-1);
}//END
