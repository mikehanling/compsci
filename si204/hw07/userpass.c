#include "si204.h"

int main() {
  fputs("Username: ", stdout);
  cstring name;
  readstring(name, stdin);
  fputs("Password: ", stdout);
  cstring pass;
  readstring(pass, stdin);
  if (strcmp(name, "supe") == 0) {
    if (strcmp(pass, "beatarmy") == 0) {
      fputs("yes", stdout);
    }else {
      fputs("no", stdout);
    }
  }else if (strcmp(name, "bbq") == 0) {
    if (strcmp(pass, "brisket") == 0) {
      fputs("yes", stdout);
    }else {
      fputs("no", stdout);
    }
  }else {
    fputs("no", stdout);
  }



  return 0;
}
