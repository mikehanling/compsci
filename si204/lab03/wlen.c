#include "si204.h"

int main() {
  fputs("Enter a filename: ", stdout);
  cstring filename;
  readstring(filename, stdin);
  stream filein = fopen(filename, "r");
  
  int wordcount = 0;
  int starcount = 0;
  cstring current;
  int lengths = 0;
  
  while (starcount < 3) {
    readstring(current, filein);
    if (strcmp(current, "***") == 0) {
      starcount += 1;
    }else if (starcount == 2) {
      wordcount += 1;
      lengths += strlen(current);
    }
  }
  fclose(filein);

  fputs("Average word length: ", stdout);
  writenum((double)lengths/wordcount, stdout);
  //fputc('\n', stdout);

  return 0;
}
