//Mike Hanling


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node node;
struct node{
  char color[128];
  node* next;
};


node* paint(char* color, node* canvas);
node* strip(node* canvas);
void print_top(node* canvas);


int main() {
  node* canvas = calloc(1, sizeof(node));
  strcpy(canvas->color, "none");
  char cmd[128];
  char color[128];
  while (1) {
    print_top(canvas);

    scanf(" %s", cmd);
    if (strcmp(cmd, "strip") == 0) {
      if (strcmp(canvas->color, "none") == 0) {
        break;
      }
      canvas = strip(canvas);
    }else if (strcmp(cmd, "paint") == 0) {
      scanf(" %s", color);
      canvas = paint(color, canvas);
    }else break;
  }

  free(canvas);

  return 0;
}


node* paint(char* color, node* canvas) {
  node* temp = calloc(1, sizeof(node));
  strcpy(temp->color, color);
  temp->next = canvas;
  return temp;
}
node* strip(node* canvas) {
  return canvas->next;
}

void print_top(node* canvas) {
  if (strcmp(canvas->color, "none") == 0) {
    printf("The canvas is blank.\n");
  }else {
    printf("The top color is %s.\n", canvas->color);
  }
}
