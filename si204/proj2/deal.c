//Mike Hanling
//deal.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


///***PROTOTYPES***///
void make_deck(int* deck, int seed);
void print_board(int* phand, int* dhand, int pcards, int dcards);
void print_value(int facevalue);
void print_suit(int suitvalue);
int* dealcard(int* hand, int* cards, int* deck);
void dealer_plays(int* dhand, int* phand, int dcards, int pcards, int* deck);


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

  int* phand = calloc(1, sizeof(int));  //player hand
  int pcards = 0;  // number of cards player has
  int* dhand = calloc(1, sizeof(int));  //dealer hand
  int dcards = 0;  //number of cards dealer has

  //deals inital two cards for each
  for (int i = 0; i < 2; i++) {
    phand = dealcard(phand, &pcards, deck);
    dhand = dealcard(dhand, &dcards, deck);
  }
  
  //prints board/deals until player stands
  char hs;
  while (1) {
    print_board(phand, dhand, pcards, dcards);
    printf("Hit or stand? [h/s] ");
    scanf(" %c", &hs);
    
    //if stand, then print board and go to dealer sequence
    if (hs == 's') {
      print_board(phand, dhand, pcards, dcards);
      break;
    }
    
    //deals a card to player
    phand = dealcard(phand, &pcards, deck);
  }

  //dealer hit/hit/stand
  dealer_plays(dhand, phand, dcards, pcards, deck);


  free(phand);
  free(dhand);
  return 0;
} //end main


///***FUNCTIONS DEFS***///
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


void print_board(int* phand, int* dhand, int pcards, int dcards) {
  
  //determines longer deck
  int cards = 0;
  if (pcards > dcards) {
    cards = pcards;
  }else {
    cards = dcards;
  }

  printf("\n Player Dealer\n");

  //for every "card" in longest hand
  for (int i = 0; i < cards; i++) {
    //decodes the face and suit values
    //player
    int pfaceval = 0; 
    int psuitval = 0;
    int dfaceval = 0;
    int dsuitval = 0;
    if (i < pcards) {
      pfaceval = phand[i] % 100;
      psuitval = phand[i] / 100;
    }
    //dealer
    if (i < dcards) {
      dfaceval = dhand[i] % 100;
      dsuitval = dhand[i] / 100;
    }

    printf("| ");

    //prints the correct face value and suit char for player
    print_value(pfaceval);
    print_suit(psuitval);
    printf("  | ");

    //prints the correct face value and suit char for dealer
    print_value(dfaceval);
    print_suit(dsuitval);
    printf("  |\n");
  } //end for

} //end print_deck


void print_value(int facevalue) {
  if (facevalue == 0) {
    printf("  ");
  }else if (facevalue == 11) {
    printf(" J");
  }else if (facevalue == 12) {
    printf(" Q");
  }else if (facevalue == 13) {
    printf(" K");
  }else if (facevalue == 14) {
    printf(" A");
  }else {
    printf("%2i", facevalue);
  }
} //end print_value


void print_suit(int suitvalue) {
  if (suitvalue == 0) {
    printf(" ");
  }else if (suitvalue == 1) {
    printf("\u2663");
  }else if (suitvalue == 2) {
    printf("\u2666");
  }else if (suitvalue == 3) {
    printf("\u2665");
  }else {
    printf("\u2660");
  }
} //end print_suit



int* dealcard(int* hand, int* cards, int* deck) {
  
  //takes last card from deck and gives it to hand
  hand[*cards] = deck[51];

  //increments num cards and adds empty element to hand for possible next card
  *cards += 1;
  hand = realloc(hand, (*cards+1) * sizeof(int));
  hand[*cards] = 0;

  //cycles deck so new card next card on top
  for (int i = 0; i < 51; i++) {
    int temp = deck[51];
    deck[51] = deck[i];
    deck[i] = temp;
  }
  
  return hand;
} //end dealcard


void dealer_plays(int* dhand, int* phand, int dcards, int pcards, int*deck) {

  //dealer sequence
  printf("Dealer hits.\n");
  sleep(2);
  dhand = dealcard(dhand, &dcards, deck);
  print_board(phand, dhand, pcards, dcards);
  printf("Dealer hits.\n");
  sleep(2);
  dhand = dealcard(dhand, &dcards, deck);
  print_board(phand, dhand, pcards, dcards);
  printf("Dealer stands.\n");

} //end dealer_plays
