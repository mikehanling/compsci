//Mike Hanling

#include <stdio.h>

struct date {
  int month;
  int day;
  int year;
};

struct person {
  char name[128];
  struct date birthday;
};

void read_person(struct person* pptr);
void write_person(struct person p);
void sort(struct person* data, int size);
int before(struct person a, struct person b);

int main() {
  printf("How many people? ");
  fflush(stdout);
  int nppl;
  scanf(" %i", &nppl);

  // create array and read in each person
  struct person people[nppl];
  for (int i=0; i < nppl; ++i) {
    read_person(&people[i]);
  }

  // sort by birthday
  sort(people, nppl);

  // print out youngest first
  printf("\nFrom youngest to oldest:\n");
  for (int i=0; i < nppl; ++i) {
    write_person(people[i]);
  }

  return 0;
}

int before(struct person a, struct person b) {
  // FIXME: YOU FILL THIS IN!!!
  if (a.birthday.year == b.birthday.year) {
    if (a.birthday.month == b.birthday.month) {
      return a.birthday.day > b.birthday.day;
    }
    return a.birthday.month > b.birthday.month;
  }
  return a.birthday.year > b.birthday.year;
}


void write_person(struct person p) {
  // FIXME: YOU FILL THIS IN!!!
  printf("%s %i/%i/%i\n", p.name, p.birthday.month, 
                                  p.birthday.day, 
                                  p.birthday.year);

}

void read_person(struct person* pptr) {
  int check = scanf(" %s %i/%i/%i",
                    pptr->name,
                    &pptr->birthday.month,
                    &pptr->birthday.day,
                    &pptr->birthday.year);
  if (check != 4) {
    printf("ERROR: invalid person format\n");
  }
}


void sort(struct person* data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (before(data[imax], data[i])) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    struct person temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}
