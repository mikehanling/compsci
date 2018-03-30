//Mike Hanling
//oddfirst.c

#include <stdio.h>
#include <stdlib.h>


int* read_nums(int length);
void selectionSort(int* data, int size);
int* splitodds(int* fullarray, int size, int* count);
int* splitevens(int* fullarray, int size, int* count);
void print_nums(int* first, int size1, int* second, int size2);


int main() {
  int len = 10;

  //reads ints
  int* nums = read_nums(len);

  //sorts ints
  selectionSort(nums, len);

  //splits odds and evens
  int oddcount = 0;
  int* odds = splitodds(nums, len, &oddcount);
  int evencount = 0;
  int* evens = splitevens(nums, len, &evencount);

  //prints odds then evens
  print_nums(odds, oddcount, evens, evencount);

  free(nums);
  free(odds);
  free(evens);

  return 0;
}


int* read_nums(int length) {
  int* nums = calloc(length, sizeof(int));

  for (int i = 0; i < length; i++) {
    scanf(" %i", &nums[i]);
  }

  return nums;
}

void selectionSort(int* data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (data[imax] < data[i]) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    int temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}


int* splitodds(int* fullarray, int size, int* count) {
  int* odds = calloc(size, sizeof(int));

  for (int i = 0; i < size; i++) {
    if (fullarray[i] % 2 == 1) {
      odds[*count] = fullarray[i];
      *count += 1;
    }
  }

  return odds;
}


int* splitevens(int* fullarray, int size, int* count) {
  int* evens = calloc(size, sizeof(int));

  for (int i = 0; i < size; i++) {
    if (fullarray[i] % 2 == 0) {
      evens[*count] = fullarray[i];
      *count += 1;
    }
  }

  return evens;
}


void print_nums(int* first, int size1, int* second, int size2) {
  for (int i = 0; i < size1; i++) {
    printf("%i ", first[i]);
  }
  for (int i = 0; i < size2; i++) {
    printf("%i ", second[i]);
  }
}
