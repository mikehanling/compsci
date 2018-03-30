#include <stdio.h>
#include "list.h"

int main() {
  struct node* L = NULL;

  char str[128];
  printf("Enter 5 words in reverse order: ");
  fflush(stdout);
  for (int i=0; i<5; ++i) {
    scanf(" %s", str);
    L = add2front(str, L);
  }

  printf("\n");
  printf("Contents in order:\n");
  print_fwd(L);

  printf("\n");
  printf("contains orange: %i\n", contains("orange", L));
  printf("contains brown: %i\n", contains("brown", L));

  printf("\n");
  printf("the string at index 2 is %s\n", get_ith(2, L));

  printf("\n");
  printf("the total number of characters is %i\n", num_chars(L));

  // uncomment once you get to these!
  printf("\n");
  printf("Contents in reverse order:\n");
  print_rev(L);

  printf("\n");
  printf("Contents after removing index 3:\n");
  L = remove_ith(3, L);
  print_fwd(L);
  

  free_list(L);

  return 0;
}
