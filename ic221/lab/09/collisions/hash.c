#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <string.h>

#include "myhashlib.h"

int main(int argc, char * argv[]){

  if(argc < 2){
    fprintf(stderr, "ERROR: require word to hash\n");
    exit(1);
  }

  int len=strlen(argv[1]);

  if(len > MSG_LEN){
    fprintf(stderr, "WARRNING: Length of greater than %d\n", MSG_LEN);
    fprintf(stderr, "Reducing: '%s'",argv[1]) ;
    argv[1][MSG_LEN]='\0';
    fprintf(stderr, " to '%s'\n",argv[1]);
    len=MSG_LEN;
  }

  char hash[HASH_LEN];
  myhash(argv[1], len, hash);
  
  printf("%s\n",hash);
}
