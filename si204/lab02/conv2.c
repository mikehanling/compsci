#include "si204.h"

int main() {
  cstring s;
  readstring(s, stdin);
  double init = readnum(stdin);
  cstring curr1;
  readstring(curr1, stdin);
  if (strcmp(curr1, "Dollars") == 0) {
    readstring(s, stdin);
    strcpy(curr1, s);
  }
  readstring(s, stdin);
  cstring curr2;
  readstring(curr2, stdin);
  if (strcmp(curr2, "Dollars") == 0) {
    readstring(s, stdin);
    strcpy(curr2, s);
  }
  double ans;

  if (strcmp(curr1, curr2) == 0) {
    ans = init;
  }else if (strcmp(curr1, "US") == 0) {
    if (strcmp(curr2, "Euros") == 0) {
      ans = init*.93000;
    }else if (strcmp(curr2, "Canadian") == 0) {
      ans = init*1.33000;
    }else {
      ans = init*114.62000;
    }
  }else if (strcmp(curr1, "Euros") == 0) {
    if (strcmp(curr2, "US") == 0) {
      ans = init/.93000;
    }else if (strcmp(curr2, "Canadian") == 0) {
      ans = init*1.33000/.93000;
    }else {
      ans = init/.93000*114.62000;
    }
  }else if (strcmp(curr1, "Canadian")== 0) {
    if (strcmp(curr2, "US") == 0) {
      ans = init/1.33000;
    }else if (strcmp(curr2, "Euros") == 0) {
      ans = init/1.33000*.93000;
    }else {
      ans = init/1.33000*114.62000;
    }
  }else{
    if (strcmp(curr2, "US") == 0) {
      ans = init/114.62000;
    }else if (strcmp(curr2, "Canadian") == 0) {
      ans = init/1.33000*114.62000;
    }else {
      ans = init/114.62000*.93000;
    }
  }

  writenum(ans, stdout);




  return 0;
}
