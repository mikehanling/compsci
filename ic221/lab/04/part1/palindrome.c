#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check1(char * str);
int check2(char * str1);

int check1(char *str){
  char* front = str;
  char* back = str;

  //traverse str to the end
  while(*back++)
    ;
  back--;   //get back to null byte
  back--;   //get to last char

  //traverse both ways, checking for equality
  while (*front) {
    if (*front++ != *back--) return 0;
  }
  return 1;
}

int check2(char *str1){
  char* trash = str1;
  char* base = str1;
  char* copy = calloc(128, sizeof(char));
  char* str2 = copy; //string to copy to

  //get a pointer to the end of the input
  while(*trash++)
    ;
  trash--;    //get back to null byte
  trash--;    //get to last character

  //copy
  while(*base++)
    *copy++ = *trash--;
  *copy = '\0';

  //return
  if(!strcmp(str1, str2)) return 1;
  return 0;
}

int main(int argc, char * argv[]){

  char str[1024];

  printf("Enter a string:\n");

  scanf("%1023s",str);

  if(check1(str)){
    printf("Palindrome according to check 1\n");
  }else{
    printf("NOT a palindrome according to check 1\n");
  }
   

  if(check2(str)){
    printf("Palindrome according to check 2\n");
  }else{
    printf("NOT a palindrome according to check 2\n");
  }
  
}
