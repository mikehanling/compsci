#include <stdio.h>
int main( int argc, char * argv[]){
  FILE* stream;

  stream = fopen("file.txt", "w");

  fprintf(stream, "Hello World");

  return 0;
}
