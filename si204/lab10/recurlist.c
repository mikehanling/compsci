//Mike Hanling
//recurlist.h

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
  //prints node and then prints the next one so on...
  if (L) {
    printf("%s\n", L->data);
    print_fwd(L->next);
  }
}


void free_list(node* L) {
  //goes to end of LL and frees in rev
  if (L) {
    free_list(L->next);
    free(L);
  }
}


int contains(char* s, node* L) {
  //checks until the end of LL for a match
  if (!L) return 0;
  if (strcmp(L->data, s) == 0) return 1;
  return contains(s, L->next);
}


char* get_ith(int i, node* L) {
  //calls recursively until temp is at the desired node
  if (i == 0) {
    return L->data;
  }else {
    return get_ith(i-1, L->next);
  }
}


int num_chars(node* L) {
  //returns string length plus the string length of the next until the end
  if (!L) {
    return 0;
  }else {
    return strlen(L->data) + num_chars(L->next);
  }
}


void print_rev(node* L) {
  //goes to the end of the list and then prints as it comes back to the front
  if (L) {
    print_rev(L->next);
  printf("%s\n", L->data);
  }
}


node* remove_ith(int i, node* L) {
  //return the LL with the desired node no longer in the chain
  if (i == 0) {
    return L->next;
  }
  if (i == 1) {
    node* temp = L->next;
    L->next = L->next->next;
    free(temp);
    return L;
  }else {
    L->next = remove_ith(i-1, L->next);
    return L;
  }
}
