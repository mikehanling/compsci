#include "si204.h"

int main() {
  fputs("Enter a filename: ", stdout);
  cstring filename;
  readstring(filename, stdin);
  stream filein = fopen(filename, "r");
  
  int wordcount = 0;
  int starcount = 0;
  cstring current;
  cstring last;
  int slengths = 0;
  int numsen = 0;
  int check = 1;
  
  while (starcount < 3) {
    readstring(current, filein);
    if (strcmp(current, "***") == 0) {
      starcount += 1;
    }else if (starcount == 2) {
      wordcount += 1;
      check = 1;
      if (strchr(current, '.') != 0 ||
          strchr(current, '?') != 0 || 
          strchr(current, '!') != 0 ) {
        numsen +=1;
        check = 0;
      }
    }
  }
  if (check) {
    numsen += 1;
  }
  fclose(filein);

  fputs("Average sentence length: ", stdout);
  writenum((double)wordcount/numsen, stdout);
  //fputc('\n', stdout);

  return 0;
}
