//Mike Hanling

#include <stdio.h>

// I want a function harm(n) that computes the nth harminic number, which
// is 1/1 + 1/2 + 1/3 + ... + 1/n.  Can you make it for me?
// Add the prototype and definition to this file that makes the program work.

double harm(int term);

int main() {
  double target;
  printf("Enter target: ");
  fflush(stdout);
  scanf(" %lg", &target);

  double curharm = 0;
  int i = 0;
  do {
    i++;
    curharm = harm(i); //-- here's where I use harm!
  } while(curharm < target);

  printf("The %ith harmonic number is %g,"
         " which is the first greater than %g.\n",
         i, curharm, target);

  return 0;
}



double harm(int term) {
  double ans = 0.0;
  for (int i = 1; i <= term; i++) {
    ans += 1/(double)i;
  }

  return ans;
}
