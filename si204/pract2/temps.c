//Mike Hanling
//temps.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {
  printf("Filename: ");
  char file[128];
  scanf(" %s", file);
  FILE* fin = fopen(file, "r");

  int days = 0;
  fscanf(fin, " %i days", &days);

  double** data = calloc(days, sizeof(double*));
  for (int i = 0; i < days; i++) {
    data[i] = calloc(24, sizeof(double));
    for (int k = 0; k < 24; k++) {
      fscanf(fin, " %lg", &data[i][k]);
    }
  }

  while (1) {
    printf("What hour? ");
    int hour;
    scanf(" %i", &hour);
    if (hour == -1) {
      break;
    }
    
    double av = 0;
    for (int i = 0; i < days; i++) {
      av += data[i][hour];
    }
    av /= days;

    printf("Average: %lg\n", av);
  }

  for (int i = 0; i < days; i++) {
    free(data[i]);
  }
  free(data);

  return 0;
}
