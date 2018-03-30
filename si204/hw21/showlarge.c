//Mike Hanling

#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPES */
double* readnumbers(int len);
void printlarger(double* data, int len, double minval);


/* MAIN */
int main () {
  //Prompt
  printf("Enter 5 numbers: ");
  fflush(stdout);
  
  //read and store input
  double* data = readnumbers(5);

  //print the ones over 100
  printf("Big ones: ");
  printlarger(data, 5, 100);
  printf("\n");


  return 0;
}  // end main


/* FUNCTION DEFINITIONS */
double* readnumbers(int len) {
  double* nums = calloc(len, sizeof(int));

  for (int i = 0; i < len; i++) {
    scanf(" %lg", &nums[i]);
  }  // end for

  return nums;
}  // end readnumbers

void printlarger(double* data, int len, double minval) {
  for (int i = 0; i < len; i++) {
    if (data[i] > minval) {
      printf("%g ", data[i]);
    }  // end if
  }  // end for
}  // end printlarger
