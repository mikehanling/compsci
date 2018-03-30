//Mike Hanling
//basic.c


#include <stdio.h>
#include <string.h>

// fills in the array with integers read from stdin
void read(int* array, int size);

// prints the array to stdout, lined up with dashes and
// corresponding capital letters underneath
void print(int* array, int size);

// returns 1 if the array elements are in ascending (non-decreasing)
// order, and otherwise returns 0.
int is_ordered(int* array, int size);

//will swap the value of a lettered column with another lettered column
void swap(int* array, char first, char second);

//will reverse board from one column to another
void reverse(int* array, char first, char last);


int main() {
  printf("Welcome to PutInOrder!\nboard: ");  
  int size;
  scanf(" N = %i :", &size);

  int board[size];
  read(board, size);
  print(board, size);

  int pts = 0;
  int moves = 0;
  char cmd[128];

  while (1) {
    //check for end of game
    if (is_ordered(board, size)) {
      printf("%i points! (%i moves)\n", pts, moves);
      return 0;
    }  //end if

    printf("command: ");
    scanf(" %s", cmd);
    if (strcmp(cmd, "swap") == 0) {
      char first, second;
      scanf(" %c %c", &first, &second);
      swap(board, first, second);
      pts += 3;
      moves += 1;
    }else if(strcmp(cmd, "reverse") == 0) {
      char first, last;      
      scanf(" %c %c", &first, &last);
      reverse(board, first, last);
      pts += 2;
      moves += 1;
    }else {
      printf("Unknown move \"%s\"\n", cmd);
    }  //end ifelse
    
    print(board, size);

  }  //end while

}  // end main


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


void swap(int* array, char first, char second) {

  //calc columns
  int col1 = (int)(first - 'A');
  int col2 = (int)(second - 'A');
  
  //swap
  int temp = array[col1];
  array[col1] = array[col2];
  array[col2] = temp;
}


void reverse(int* array, char first, char last) {
  //calc columns
  int col1 = (int)(first - 'A');
  int col2 = (int)(last - 'A');

  //reverse (RH boolean arg is how many times are needed to swap
  for (int i = 0; i < (((col2 - col1) + 2) / 2); i++) {
    swap(array, first+i, last-i);
  }  //end for

}  //end reverse
