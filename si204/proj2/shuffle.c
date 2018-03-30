//Mike Hanling
//shuffle.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


///***PROTOTYPES***///
void make_deck(int* deck, int seed);
void print_deck(int* deck);


///***MAIN***///
int main() {
  
  //attain seed value
  printf("Seed: ");
  int seed = 0;
  if (scanf(" %i", &seed) != 1) {
    printf("ERROR: must be an integer value for seed");
    return 1;
  }

  //creates, shuffles, and prints the deck out to the user
  int deck[52];
  make_deck(deck, seed);
  print_deck(deck);


  return 0;
} //end main


void make_deck(int* deck, int seed) {
  
  //create unshuffled deck
  int faceval = 2;
  int suitval = 1;
  for (int i = 0; i < 52; i++) {  //hard coded 52 because every deck is same
    deck[i] = (100*suitval) + faceval;
    faceval++;
    if (faceval > 14) {
      faceval = 2;
      suitval++;
    } //end if

  } //end for
  

  //returns unshuffled deck if seed is 0
  if (seed == 0) {
    return;
  }


  //shuffles deck with given seed
  srand(seed);
  for (int swap1 = 0; swap1 < 52; swap1++) {
    int swap2 = rand() % 52;
    int temp = deck[swap1];
    deck[swap1] = deck[swap2];
    deck[swap2] = temp;
  }

  
  //returns shuffled deck
  return;

} //end make_deck


void print_deck(int* deck) {
  
  //for every "card"
  for (int i = 0; i < 52; i++) {
    //decodes the face and suit values
    int faceval = deck[i] % 100;
    int suitval = deck[i] / 100;

    //prints the correct face value
    if (faceval == 11) {
      printf(" J");
    }else if (faceval == 12) {
      printf(" Q");
    }else if (faceval == 13) {
      printf(" K");
    }else if (faceval == 14) {
      printf(" A");
    }else {
      printf("%2i", faceval);
    }


    //prints correct suit char
    if (suitval == 1) {
      printf("\u2663\n");
    }else if (suitval == 2) {
      printf("\u2666\n");
    }else if (suitval == 3) {
      printf("\u2665\n");
    }else {
      printf("\u2660\n");
    }
  
  } //end for

} //end print_deck
