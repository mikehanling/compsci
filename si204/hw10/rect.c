#include "si204.h"

int main() {
  fputs("Height: ", stdout);
  int height = readnum(stdin);
  fputs("Width: ", stdout);
  int width = readnum(stdin);
  fputs("Offset: ", stdout);
  int offset = readnum(stdin);

  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < offset; ++j) {
      fputc(' ', stdout);
    }
    for (int k = 0; k < width; ++k) {
      if (i == 0 || i == (height-1)) {
        fputc('*', stdout);
      }else if (k == 0 || k == (width-1)) {
        fputc('*', stdout);
      }else {
        fputc(' ', stdout);
      }
    }
    fputc('\n', stdout);
  }


  return 0;
}
