#include <stdio.h>
#include <string.h>

double average(double x, double y, double z);

int main() {
  printf("Enter three numbers: ");
  double x = 0.0;
  double y = 0.0;
  double z = 0.0;
  scanf(" %lg %lg %lg", &x, &y, &z);

  printf("The average is %g\n", average(x, y, z));

  return 0;
}

double average(double x, double y, double z) {
  return (x + y + z) / 3;
}
