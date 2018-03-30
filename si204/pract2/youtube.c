//Mike Hanling
//youtube.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void selectionSort(double* data, int size);
int before(double a, double b);


int main() {
  int numv = 10;
  double* times = calloc(numv, sizeof(double));
  printf("How long are the videos? ");
  for (int i = 0; i < numv; i++) {
    scanf(" %lg", &times[i]);
  }

  
  selectionSort(times, numv);

  double twatch = 0;
  int vwatch = 0;

  while (vwatch < 10) {
    double temp = twatch + times[vwatch];
    if (temp <= 55) { 
      twatch += times[vwatch];
      vwatch++;
    }else {
      break;
    }
  }

  printf("You can watch %i videos in %g minutes\n", vwatch, twatch);

  free(times);

  return 0;
}

void selectionSort(double* data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (before(data[imax], data[i])) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    double temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}

//this is make array sorted least to greatest
int before(double a, double b) {
  return a < b;
}

