//Postfix Calculator
//
//Can do + - * / ^ $(this is sqaure)
//
//Works with floats
//
//Each operator/operand must be spaced

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node node;
struct node{
  float data;
  node* next;
};

node* add2front(float val, node* list);
node* delfirst(node* list);
int isDigit(char c);
float Number(char* c);
int isOperator(char c);
node* Operate(char c, node* stack);

int main() {
  //ask for expression and initiate nodelist
  printf("Enter Postfix expression:\n");
  node* stack = NULL;

  //read in each char and determine if number or operator
  char c;
  while (scanf("%c", &c) == 1 && c != '\n') {
    if (c == ' ') continue;  //disregard whitespace
    else if (isDigit(c)) {  //for number, complete number and store
      stack = add2front(Number(&c), stack);
    }else if (isOperator(c)) {  //for operators pop as need and store answer
      stack = Operate(c, stack);
    }else {  //for anything not specified, exit
      printf("Invalid characters.\n");
      return 1;
    }
  }
  
  //check that there is only one number left in stack
  if (stack->next == NULL) {
    printf("= %g\n", stack->data);
  }else {  //in extra nodes then not valid
    printf("Invalid postfix expression.\n");
    return 3;
  }

  return 0;
}



node* add2front(float val, node* list) {
  node* temp = calloc(1, sizeof(node));
  temp->data = val;
  temp->next = list;
  return temp;
}

node* delfirst(node* list) {
  return list->next;
}

int isDigit(char c) {
  int num = (int)c - 48;
  if (num > -1 && num < 10) return 1;
  else return 0;
}

float Number(char* c) {
  float num = 0.0;
  while (*c != '.' && *c != ' ') {
    //check for single number input
    if (*c == '\n') return num;
    //check for any nondigits in number
    if (*c < 48 || *c > 57) {
      printf("Invalid number.\n");
      return 2;
    }
    num = num*10 + ((int)*c - 48.0);
    scanf("%c", c);
  }
  if (*c == '.') scanf("%c", c);
  while (*c != ' ') {
    //check for any nondigits in number
    if (*c < 48 || *c > 57) {
      printf("Invalid number.\n");
      return 2;
    }
    num = (num*10 + ((int)*c - 48.0))/10;
    scanf("%c", c);
  }
  
  return num;
}
  
int isOperator(char c) {
  if (c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='$') return 1;
  else return 0;
}

node* Operate(char c, node* stack) {
  if (c == '+') {
    //get numbers from stack
    float num2 = stack->data;
    stack = delfirst(stack);
    float num1 = stack->data;
    stack = delfirst(stack);
    
    //push answer to stack
    stack = add2front(num1+num2, stack);
  }else if (c == '-') {
    //get numbers from stack
    float num2 = stack->data;
    stack = delfirst(stack);
    float num1 = stack->data;
    stack = delfirst(stack);
    
    //push answer to stack
    stack = add2front(num1-num2, stack);
  }else if (c == '*') {
    //get numbers from stack
    float num2 = stack->data;
    stack = delfirst(stack);
    float num1 = stack->data;
    stack = delfirst(stack);
    
    //push answer to stack
    stack = add2front(num1*num2, stack);
  }else if (c == '/') {
    //get numbers from stack
    float num2 = stack->data;
    stack = delfirst(stack);
    float num1 = stack->data;
    stack = delfirst(stack);
    
    //push answer to stack
    stack = add2front(num1/num2, stack);
  }else if (c == '^') {
    //get numbers from stack
    float num2 = stack->data;
    stack = delfirst(stack);
    float num1 = stack->data;
    stack = delfirst(stack);
    
    float ans = 1.0;
    for (int i = 0; i < num2; i++) {
      ans *= num1;
    }

    //push answer to stack
    stack = add2front(ans, stack);
  }else if (c == '$') {
    //get numbers from stack
    float num1 = stack->data;
    stack = delfirst(stack);
    
    //push answer to stack
    stack = add2front(num1*num1, stack);
  }

  return stack;
}
