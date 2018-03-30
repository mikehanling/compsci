//Mike Hanling
//basic.c


#include <stdio.h>
#include <string.h>


///***PROTOTYPES***////

// fills in the array with integers read from stdin
void read(int* array, int size, FILE* in);

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

//will return the largest number in array
int getlarge(int* array, int size);

//will cycle all column to the left
void cleft(int* array, int size);


///***MAIN***///
int main() {
  printf("Welcome to PutInOrder!\nboard: ");  
  int size;

  //determine stdin or file
  FILE* in = stdin;
  if (scanf(" N = %i :", &size) != 1) {
    char file[128];
    scanf(" %s", file);
    in = fopen(file, "r");
    fscanf(in, " N = %i :", &size);
  }  //end if
  
  //set up initial board
  int board[size];
  read(board, size, in);
  print(board, size);

  int pts = 0;
  int moves = 0;
  char cmd[128];

  //PLAY THE GAME!!!
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
    }else if (strcmp(cmd, "cycleleft") == 0) {
      int shifts = 0;
      scanf(" %i", &shifts);
      for (int i = 0; i < shifts; i++) {
        cleft(board, size);
      }
      pts += 1;
      moves += 1;
    }else {
      printf("Unknown move \"%s\"\n", cmd);
    }  //end ifelse
    
    print(board, size);

  }  //end while
  //END PLAYING GAME!!!

}  // end main


///***Function Definitions***///
void read(int* array, int size, FILE* in) {
  for (int i = 0; i < size; i++) {
    fscanf(in, " %i", &array[i]);
  } // end for

}  //end read


void print(int* array, int size) {
  //print graphic
  int curr = getlarge(array, size);
  while (curr > 0) { 
    for (int k = 0; k < size; k++) {
      if (array[k] >= curr) {
        printf(" #");
      }else {
        printf("  "); //two spaces
      }  //end ifelse
    
    }  //end for

    printf("\n");
    curr--;
  }  //end while
    
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


int getlarge(int* array, int size) {
  int big = array[0];
  for (int i = 0; i < size-1; i++) {
    if (array[i+1] > big) {
      big = array[i+1];
    }  //end if

  }  //enf for

  return big;
}  //end getlarge


void cleft(int* array, int size) {
  char first = 'A';
  char second = first + (size-1);
  
  //swap ends, then first and next to last...
  for (int i = 0; i < (size-1); i++) {
    swap(array, first, second);
    second -= 1;
  }  //end for (inner)


}  //end cleft
