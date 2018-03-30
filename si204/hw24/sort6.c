//Mike Hanling
//sort6.c


#include <stdio.h>
#include<stdlib.h>


void bigLittle(int* array, int size);


int main() {
  int length = 6;
  
  //make the array from given numbers
  printf("Enter %i numbers: ", length);
  int nums[length];
  for (int i = 0; i < length; i++) {
    scanf(" %i", &nums[i]);
  }

  //sort the numbers
  bigLittle(nums, length);

  //print the sorted array out
  for (int k = 0; k < length; k++) {
    printf("%i\n", nums[k]);
  }


  return 0;
}


void bigLittle(int* array, int size) {
  for (int i = size; i > 1; i--) {
    int imin = 0;
    for (int k = 1; k < i; k++) {
      if (array[k] < array[imin]) {
        imin = k;
      }
    }

    int temp = array[i-1];
    array[i-1] = array[imin];
    array[imin] = temp;
  }/*
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (array[imax] > array[i]) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    int temp = array[imax];
    array[imax] = array[length - 1];
    array[length - 1] = temp;
  }*/

}
