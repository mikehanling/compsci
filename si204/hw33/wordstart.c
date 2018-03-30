//Mike Hanling
//wordstat.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node node;
struct node{
  char data[128];
  node* next;
};


node* add2front(char* data, node* list);


int main() {
  printf("Enter words followed by END:\n");

  node* words = calloc(1, sizeof(node));
  scanf(" %s", words->data);
  char w[128];
  while (scanf(" %s", w) == 1 && strcmp(w, "END") != 0) {
    words = add2front(w, words);
  }

  printf("What letter? ");
  char letter;
  scanf(" %c", &letter);

  for (node* cur = words; cur; cur = cur->next) {
    if (cur->data[0] == letter) {
      printf("%s\n", cur->data);
    }
  }

  while (words) {
    node* temp = words->next;
    free(words);
    words = temp;
  }

  return 0;
}


node* add2front(char* data, node* list) {
  node* temp = calloc(1, sizeof(node));
  strcpy(temp->data, data);
  temp->next = list;
  return temp;
}
  
