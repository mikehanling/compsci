//Mike Hanling

#include <stdio.h>

int main() {
  //read in length
  printf("How many numbers? ");
  fflush(stdout);
  int length = 0;
  scanf(" %i", &length);
  
  //read in numbers
  printf("Enter %i numbers: ", length);
  fflush(stdout);

  int nums[length];
  for (int i = 0; i < length; i++) {
    scanf(" %i", &nums[i]);
  }

  //print the reverse
  for (int j = length; j > 0; j--) {
    printf("%i\n", nums[j-1]);
  }


  return 0;
}
