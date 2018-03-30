#include <stdlib.h>
#include <stdio.h>
#include <openssl/sha.h>

#include "myhashlib.h"

//A hash function


//DO NOT EDIT
void myhash(char * msg, int len, char * hash){
  
  unsigned char digest[SHA_DIGEST_LENGTH];
  SHA1((unsigned char *) msg,len,digest);
  
  int i;
  for(i=0;i<HASH_LEN/2;i++){
    sprintf(hash + (i*2),"%02hhx",digest[i]);
  }
  digest[HASH_LEN] = '\0';
  
}


