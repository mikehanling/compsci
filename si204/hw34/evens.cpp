//Mike Hanling
//evens.cpp

#include <cstdio>


int* readnum(int& size);
bool isEven(int x);


int main() {
  //make input array
  int num = 0;
  int* input = readnum(num);

  //subtract if num is odd
  for (int i = 0; i < num; i++) {
    if (!isEven(input[i])) num--;
  }

  //print answer
  printf("%i even numbers\n", num);

  //delete
  delete [] input;
  return 0;
}


int* readnum(int& size) {
  //change value of size to user input
  printf("How many numbers? ");
  scanf(" %i", &size);

  //construct the array
  int* ans = new int[size];
  for (int i = 0; i < size; i++) {
    scanf(" %i", &ans[i]);
  }

  //return the array
  return ans;
}

bool isEven(int x) {
  if (x % 2 == 0) return true;
  return false;
}
