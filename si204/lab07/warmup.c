//Mike Hanling
//warmup.c


#include <stdio.h>

// fills in the array with integers read from stdin
void read(int* array, int size);

// prints the array to stdout, lined up with dashes and
// corresponding capital letters underneath
void print(int* array, int size);

// returns 1 if the array elements are in ascending (non-decreasing)
// order, and otherwise returns 0.
int is_ordered(int* array, int size);

int main() {
  int size;
  scanf(" N = %i :", &size);

  int arr[size];
  read(arr, size);

  print(arr, size);

  if (is_ordered(arr, size)) {
    printf("Is in order!\n");
  } else {
    printf("Is not in order!\n");
  }

  return 0;
}


void read(int* array, int size) {
  for (int i = 0; i < size; i++) {
    scanf(" %i", &array[i]);
  } // end for

}  //end read


void print(int* array, int size) {
  //print array
  for (int i = 0; i < size; i++) {
    printf(" %i", array[i]);
  }  //end for
  printf("\n");
  
  //print dashes - there are two dashes per input plus one at the end
  for (int i = 0; i < 2*size+1; i++) {
    printf("-");
  }  //end for
  printf("\n");
  
  //print letters
  char letter = 'A';
  for (int j = 0; j < size; j++) {
    printf(" %c", letter);
    letter += 1;  //get next letter
  }  //end for

  printf("\n");

}  //end print


int is_ordered(int* array, int size) {
  for (int i = 0; i < size-1; i++) {
    //if any comparison is descending return false
    if (! (array[i] <= array[i+1])) {
      return 0;
    }  //end if
  
  }  //end for

  return 1;
}  //end is_ordered
