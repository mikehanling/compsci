/**************************************
This program simply reads in a bunch
of strings and sorts them.  Whoopee!
**************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**************************************
 ** PROTOTYPES
 **************************************/
void selectionSort(char** data, int size);
int before(char* a, char* b);

/**************************************
 ** MAIN FUNCTION
 **************************************/
int main() {
  // Get number of strings
  int howmany;
  printf("Enter number of strings: ");
  fflush(stdout);
  scanf(" %d", &howmany);

  // Create and populate array
  char** data = calloc(howmany, sizeof(char*));
  printf("Enter strings:\n");
  for(int i = 0; i < howmany; ++i) {
    data[i] = calloc(128, sizeof(char));
    scanf(" %s", data[i]);
  }

  // Sort!
  selectionSort(data, howmany);

  // Print in sorted order
  for(int i = 0; i < howmany; ++i) {
    printf("%s\n", data[i]);
  }

  // clean-up
  for (int i=0; i < howmany; ++i) {
    free(data[i]);
  }
  free(data);

  return 0;
}

/**************************************
 ** FUNCTION DEFINITIONS
 **************************************/

int before(char* a, char* b) {
  return strcmp(a, b) < 0;
}

void selectionSort(char** data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (before(data[imax], data[i])) {
	imax = i;
      }
    }
    // Swap data[imax] & the last element
    char* temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}
