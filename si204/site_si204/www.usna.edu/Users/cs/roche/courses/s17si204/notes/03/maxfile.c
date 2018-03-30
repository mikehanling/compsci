/***************************************************
Process Directory File information to find largest
file.

Write a program that reads the output of my
directry listing, which looks like this:

-rw-r--r-- 1 roche scs  14509 Jan  8 04:31 compile.png
-rw-r--r-- 1 roche scs 492923 Jan  7 17:56 diagram.png
    .
    .
    .
-rw-r--r-- 1 roche scs  13686 Jan  8 04:33 run-hello.png
roche@ubuntu $

... and prints out the size and name of the largest
file in the directory.  [File size (in bytes) is listed
after the word "scs".]
***************************************************/
#include "si204.h"

int main() {
  // initialization
  cstring part; // will store each part we read in
  int maxsize = -1;
  cstring maxname;
  strcpy(maxname, "ERROR");

  // read first part of first line
  readstring(part, stdin);

  // "roche@ubuntu" indicates the end
  while (strcmp(part, "roche@ubuntu") != 0) {
    // will hold the size and name of the file on this line
    int size;
    cstring name;

    // read in all parts of the line
    readstring(part, stdin); // 1 (reference count)
    readstring(part, stdin); // roche (owner)
    readstring(part, stdin); // scs (group)
    size = readnum(stdin); // FILE SIZE IN BYTES
    readstring(part, stdin); // Jan (month)
    readstring(part, stdin); // 8 (day)
    readstring(part, stdin); // 04:31 (time)
    readstring(name, stdin); // FILE NAME

    // update maxsize and maxname if needed
    if (size > maxsize) {
      maxsize = size;
      strcpy(maxname, name);
    }

    // Read first part of next line
    readstring(part, stdin);
  }

  // write result
  fputs("The largest file is ", stdout);
  fputs(maxname, stdout);
  fputs(" with ", stdout);
  writenum(maxsize, stdout);
  fputs(" bytes.\n", stdout);

  return 0;
}
