//Mike Hanling


#include <stdio.h>


void readin(double* array, int size);
void printpairs(double* array1, double* array2, int size);


int main() {
  int numpairs = 0;
  
  printf("N: ");
  fflush(stdout);
  scanf(" %i", &numpairs);

  double x[numpairs];
  double y[numpairs];

  printf("x values: ");
  fflush(stdout);
  readin(x, numpairs);
  printf("y values: ");
  fflush(stdout);
  readin(y, numpairs);

  printpairs(x, y, numpairs);
  
  return 0;
}  //end main


void readin(double* array, int size){
  for (int i = 0; i < size; i++) {
    scanf(" %lg", &array[i]);
  }
}


void printpairs(double* array1, double* array2, int size) {
  for (int i = 0; i < size; i++) {
    printf("(%g,%g) ", array1[i], array2[i]);
  }
  printf("\n");
}
