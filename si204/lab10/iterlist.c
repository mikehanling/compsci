//Mike Hanling
//iterlist.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


///***DEFINITIONS***///


node* add2front(char* s, node* L) {
  node* temp = calloc(1, sizeof(node));
  strcpy(temp->data, s);
  temp->next = L;
  return temp;
}


void print_fwd(node* L) {
  //print LL forward (rev of original order
  for (node* cur = L; cur; cur = cur->next) {
    printf("%s\n", cur->data);
  }
}


void free_list(node* L) {
  //frees every node of LL
  while (L) {
    node* temp = L;
    L = L->next;
    free(temp);
  }
}


int contains(char* s, node* L) {
  //checks every string until match or end LL
  for (node* cur = L; cur; cur = cur->next) {
    if (strcmp(cur->data, s) == 0) return 1;
  }
  return 0;
}


char* get_ith(int i, node* L) {
  //moves the front of a temp list to the correct postion to extract data
  node* temp = L;
  while (i > 0) {
    temp = temp->next;
    i--;
  }
  return temp->data;
}


int num_chars(node* L) {
  //goes through every element of LL and adds string lengths
  int tot = 0;
  for (node* cur = L; cur; cur = cur->next) {
    tot += strlen(cur->data);
  }
  return tot;
}


void print_rev(node* L) {
  //prints the LL in rev (original order of input)
  node* temp = calloc (1, sizeof(node));
  strcpy(temp->data, L->data);
  for (node* cur = L->next; cur; cur = cur->next) {
    temp = add2front(cur->data, temp);
  }

  print_fwd(temp);
  free_list(temp);
}


node* remove_ith(int i, node* L) {
  //take the element of choice of of LL
  node* temp = L;
  while (i > 1) {
    temp = temp->next;
    i--;
  }
  temp->next = temp->next->next;
  return temp;
}
