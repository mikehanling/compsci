//Mike Hanling
//IC221 Proj01
//wc.c

#include "stdio.h"
#include "ctype.h"
#include "string.h"


int main(int argc, char* argv[]) {
  //parse the options & store number of values to output
  //catch option errors
  int l = 0;
  int w = 0;
  int c = 0;
  int numOps = 0;
  for (int i = 1; i <= 3; i++) {
    if (argv[i][0] != '-') break;   //no options given
    if (strlen(argv[i]) == 2) {      
      if (argv[i][1] == 'l') {
        l = 1;
        numOps++;
      }
      if (argv[i][1] == 'w') {
        w = 1;
        numOps++;
      }
      if (argv[i][1] == 'c') {
        c = 1;
        numOps++;
      }
      if (argv[i][1] != 'w' && argv[i][1] != 'l' && argv[i][1] != 'c') {
        //not a valid one letter option
        printf("ERROR: unknown option %s\n", argv[i]);
        return 1;
      }
    }else {
      //too many letters to be a valid option
      printf("ERROR: unknown option %s\n", argv[i]);
      return 1;
    }
  }

  //determine number of files & create int* for their values in overall int**
  int numFiles = argc - numOps - 1;   //the 1 is for the run command
  int returnVals[numFiles][3];        //for lines (0), words (1), and chars (2)
  int totals[3] = {0,0,0};            //another set for the totals

  //for each file...
  for (int i = 0; i < numFiles; i++) {
    //open the file for reading, catching filename errors
    char* filename = argv[i + numOps + 1];
    FILE* fin;
    if ((fin = fopen(filename, "r")) == NULL)
      printf("ERROR: file '%s' cannot be oppened\n", filename);

    //walk through each character in file
    //add to count for lines, words, and chars appropriately
    //add to totals as working each file
    int cur = fgetc(fin);
    returnVals[i][0] = 0;
    returnVals[i][1] = 0;
    returnVals[i][2] = 0;
    printf("Right before while loop: %c\n", cur);
    while (cur != EOF) {
      printf("In while...\n");
      if (cur == '\n') { 
        printf("New Line\n");
        returnVals[i][0]++;       //line completed
        totals[0]++;
        returnVals[i][1]++;       //also word completed
        totals[1]++;
      }else if (isspace(cur)) {
        printf("Word\n");
        returnVals[i][1]++;       //word completed
        totals[1]++;
        returnVals[i][2]++;       //also a char
        totals[2]++;
      }else {
        printf("Char\n");
        returnVals[i][2]++;       //char found
        totals[2]++;
      }
      cur = fgetc(fin);
    }
  }

  //print the files in order w/ their values
  for (int i = 0; i < numFiles; i++) {
    printf("%s %d %d %d\n", argv[i + numOps + 1], returnVals[i][0],
                                                  returnVals[i][1],
                                                  returnVals[i][2]);
  }

  //print totals
  printf("total %d %d %d\n", totals[0], totals[1], totals[2]);

  return 0;
}
