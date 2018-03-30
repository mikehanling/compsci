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
    if (argc == 1) break;           //no options or files (stdinOnly)
    if (argv[i][0] != '-') break;   //no options given
    if (strlen(argv[i]) == 2) {      
      if (argv[i][1] == 'l') {
        l = 1;
        numOps++;
      }//fi

      if (argv[i][1] == 'w') {
        w = 1;
        numOps++;
      }//fi
      
      if (argv[i][1] == 'c') {
        c = 1;
        numOps++;
      }//fi
      
      if (argv[i][1] != 'w' && argv[i][1] != 'l' && argv[i][1] != 'c') {
        //not a valid one letter option
        fprintf(stderr, "ERROR: unknown option %s\n", argv[i]);
        return 1;
      }//fi
    }else {
      //too many letters to be a valid option
      fprintf(stderr, "ERROR: unknown option %s\n", argv[i]);
      return 1;
    }//fi
  }//enf for

  //determine number of files & create int* for their values in overall int**
  int numFiles = argc - numOps - 1;   //the 1 is for the run command
  int totals[3] = {0,0,0};            //lines, words, chars
  int stdinOnly = 0;
  if (numFiles == 0) {
    stdinOnly = 1;
    numFiles = 1;   //so it goes in the for loop once
  }//fi

  //for each file...
  for (int i = 0; i < numFiles; i++) {
    int lines = 0;
    int words = 0;
    int chars = 0;

    //open the file for reading, catching filename errors
    char filename[64];
    FILE* fin;
    //account for stdin being used
    if (stdinOnly || (strcmp(argv[i + numOps + 1], "+") == 0)) {
      fin = stdin;
      strcpy(filename, "-stdin-");
    }else {
      strcpy(filename, argv[i + numOps + 1]);
      if ((fin = fopen(filename, "r")) == NULL) {
        fprintf(stderr, "ERROR: file '%s' cannot be opened\n", filename);
        continue;
      }//fi
    }//fi

    //walk through each character in file
    //add to count for lines, words, and chars appropriately
    //add to totals as working each file
    int cur = fgetc(fin);
    int last = '\n';       //does not correlate to any char being checked
    while (cur != EOF) {
      
      //every time through is a char no matter what
      chars++;
      totals[2]++;

      //always a new line at \n
      if (cur == '\n') { 
        lines++;
        totals[0]++;
      }//fi

      //one or more chars followed by whitespace is a word
      if (isspace(cur) && !isspace(last)) {
        words++;
        totals[1]++;
      }//fi

      //update vars
      last = cur;
      cur = fgetc(fin);
    }//end while

    //print the data for this file
    if (l + w + c == 0)
      printf("%s %d %d %d\n", filename, lines, words, chars);
    else {    //partials
      printf("%s ", filename);
      if (l) printf("%d ", lines);
      if (w) printf("%d ", words);
      if (c) printf("%d ", chars);
      printf("\n");
    }//fi

  }//end for


  //print totals
  //all
  if (numFiles > 1) {
    if (l + w + c == 0)
      printf("total %d %d %d\n", totals[0], totals[1], totals[2]);
    else {      //partials
      printf("total ");
      if (l) printf("%d ", totals[0]);
      if (w) printf("%d ", totals[1]);
      if (c) printf("%d ", totals[2]);
      printf("\n");
    }//fi
  }//fi
    

  return 0;
}
