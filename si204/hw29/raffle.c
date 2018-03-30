//Mike Hanling
//raffle.c


#include <stdio.h>
#include <stdlib.h>


typedef struct{
  char* name;
  int* tickets;
} person;


person makePerson(int which);
int search(int* data, int size, int x);
int match(int a, int b);


int main() {
  //get number of people
  printf("How many people? ");
  int numpeople = 0;
  scanf(" %i", &numpeople);

  //make each person
  person* persons = calloc(numpeople, sizeof(person));
  for (int i = 0; i < numpeople; i++) {
    persons[i] = makePerson(i);
  }

  //get winning ticket
  printf("Winning ticket: ");
  int winning;
  scanf(" %i", &winning);

  //find and print winners
  for (int i = 0; i < numpeople; i++) {
    if (search(persons[i].tickets, 4, winning) != 4) {
      printf("%s won!\n", persons[i].name);
    }
    free(persons[i].name);
    free(persons[i].tickets);
  }

  free(persons);
  return 0;
}


person makePerson(int which) {
  char* name = calloc(128, sizeof(char));
  int* tix = calloc(4, sizeof(int));

  printf("Person %i name: ", which+1);
  scanf(" %s", name);
  printf("Person %i tickets: ", which+1);
  for (int i = 0; i < 4; i++) {
    scanf(" %i", &tix[i]);
  }

  person out = {name, tix};
  return out;
}


int search(int* data, int size, int x) {
  int i = 0;
  while(i < size && !match(data[i], x)) {
    i++;
  }
  return i;
}

int match(int a, int b) {
  return a == b;
}


