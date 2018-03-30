//Mike Hanling
#include <stdio.h>
typedef char cstring[128];

int main() {
  //read in filename and open it
  cstring filename;
  printf("Filename: ");
  scanf(" %s", filename);
  FILE* fin = fopen(filename, "r");

  double current = 0;  //current value in file
  double ans = 0;  //sum total of currents

  //reads through each number until the file's end
  while (fscanf(fin, " %lg", &current) >= 0) { 
    ans += current;
  }
  fclose(fin);

  //print answer to user
  printf("%g", ans);


  return 0;
}
