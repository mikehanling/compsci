//Mike Hanling
//back3.c


#include <stdio.h>
#include <stdlib.h>

typedef struct node node;

struct node{
  int data;
  node* next;
};

node* add2front(int val, node* list);


int main() {
  int newnum = 0;
  node* nums = NULL;

  while (1) {
    scanf(" %i", &newnum);
    if (newnum < 0) {
      break;
    }
    nums = add2front(newnum, nums);
  }

  int ans = nums->next->next->data;
  printf("%i\n", ans);

  return 0;
}

node* add2front(int val, node* list) {
  node* temp = calloc(1, sizeof(node));
  temp->data = val;
  temp->next = list;
  return temp;
}
