#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]){

  //no card numbr given ERROR
  if (argc < 2) {
    fprintf(stderr, "ERROR: require credit card number\n");
    return 1;
  }

  //card number not 16 digits ERROR
  if (strlen(argv[1]) != 16) {
    fprintf(stderr, "ERROR: Invalid credit card number: Bad Length\n");
    return 1;
  }
  
  //get ints from card number
  int sum= 0;
  for (int k = 0; k < 16; k++) {
    int cur = 0;
    
    if (argv[1][k] >= '0' && argv[1][k] <= '9') {
      //actual number
      cur = argv[1][k] - 48;

      //double even indexed
      if (k % 2 == 0) {
        cur *= 2;

        //sum digits if over 9
        if (cur > 9)
          cur = (cur % 10) + 1;    //no number will be over 20 so this works
      }
    }else {
      //letters in card number ERROR
      fprintf(stderr, "ERROR: Invalid credit card number: Bad number '%c'\n", argv[1][k]);
      return 1;
    }
    sum += cur;
  }

  // OUTPUT strinsg for you to use to pass automated tests
  if (sum % 10 == 0) {
    printf("VALID\n");
    return 0;
  }else {
    printf("INVALID\n");
    return 2;
  }
  // RETURN values to use
  //  -- return 0 : valid credit card number
  //  -- return 1 : error occured
  //  -- return 2 : invalid credit card number


}
