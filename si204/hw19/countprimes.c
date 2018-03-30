//Mike Hanling


#include <stdio.h>
#include <string.h>


int isprime(int n);
int getnum(int atleast);
int countprimes(int a, int b);


int main() {
  int low = getnum(1);
  int high = getnum(low);
  int ans = countprimes(low, high);
  printf("There are %i primes between %i and %i.\n", ans, low, high);

  return 0;
}


int isprime(int n) {
// Determines whether n is a prime number.
// If it is, 1 is returned, and if not, 0 is returned.
  if (n < 2) {
    // 2 is the smallest prime.
    return 0;
  }

  // try all possible divisors of n
  for (int fact=2; fact*fact <= n; ++fact) {
    if (n % fact == 0) {
      // n is divisible by fact, so not a prime
      return 0;
    }
  }

  // n doesn't have ANY factors, so it's a prime.
  return 1;
}


int getnum(int atleast) {
  int curr = 0;
  printf("Enter a number at least %i: ", atleast);
  scanf(" %i", &curr);
  if (curr < atleast) {
    printf("Too small!\n");
    curr = getnum(atleast);
  }

  return curr;
}


int countprimes(int a, int b) {
  int count = 0;
  
  if (a > b) {
    return 0;
  }

  return isprime(a) + countprimes(a+1, b);
}
