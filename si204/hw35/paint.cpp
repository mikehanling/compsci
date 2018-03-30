//Mike Hanling


#include <cstdio>
#include <cstdlib>
#include <cstring>


struct node{
  char color[128];
  node* next;
};


node* paint(char* color, node* canvas);
node* strip(node* canvas);
void print_top(node* canvas);
void delete_list(node* canvas);


int main() {
  node* canvas = new node[1];
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

  delete_list(canvas);

  return 0;
}


node* paint(char* color, node* canvas) {
  node* temp = new node[1];
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


void delete_list(node* canvas) {
  if (canvas) {
    delete_list(canvas->next);
    delete canvas;
  }
}
