#include "si204.h"

int main() {
  fputs("Enter a filename: ", stdout);
  cstring filename;
  readstring(filename, stdin);
  stream filein = fopen(filename, "r");
  
  int wordcount = 0;
  int starcount = 0;
  cstring current;
  int go = 1;
  
  while (go) {
    readstring(current, filein);
    if (strcmp(current, "***") == 0) {
      starcount += 1;
    }else if (starcount == 2) {
      wordcount += 1;
    }
    if (starcount == 3) {
      go = 0;
    }
  }
  fclose(filein);

  fputs("Word count: ", stdout);
  writenum(wordcount, stdout);
  //fputc('\n', stdout);

  return 0;
}
