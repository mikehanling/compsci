#include <stdio.h>
#include <stdlib.h>

int main(){
  unsigned int a = 0xcafebabe;
  unsigned char *p = (unsigned char *) &a;
  int i;

  for(i=0;i<4;i++){
    printf("%d: 0x%02x\n", i, p[i]);
  }

}

