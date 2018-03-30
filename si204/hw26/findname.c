//Mike Hanling


#include <stdio.h>
#include <stdlib.h>


int search(char** data, int size, char x);
int match(char a, char b);


int main() {
  //get list of names
  printf("Enter 5 names: ");
  char** names = calloc(5, sizeof(char*));
  for (int i = 0; i < 5; i++) {
    names[i] = calloc(128, sizeof(char));
    scanf(" %s", names[i]);
  }
  
  //ask for target letter
  char target;
  printf("Letter: ");
  scanf(" %c", &target);

  //find first name to start with target
  int ians = search(names, 5, target);

  //print result
  if (ians == 5) {
    printf("not found\n");
  }else {
    printf("%s\n", names[ians]);
  }

  return 0;
}


int search(char** data, int size, char x) {
  int i = 0;
  while(i < size && !match(data[i][0], x)) {
    i++;
  }
  return i;
}

int match(char a, char b) {
  if (a > 'A' && a < 'Z') {
    a += 'A' - 'a';
  }
  if (b > 'A' && b < 'Z') {
    b += 'A' - 'a';
  }

  return a == b;
}

