//Mike Hanling
//play.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


///***PROTOTYPES***///
void make_deck(int* deck, int seed);
void print_board(int* phand, int* dhand, int pcards, int dcards);
void print_value(int facevalue);
void print_suit(int suitvalue);
int* dealcard(int* hand, int* cards, int* pts, int* deck);
int player_plays(int* phand, int* pcards, int* ppts, int *deck);
int dealer_plays(int* dhand, int* dcards, int* dpts,int ppts, int* deck);
void reset_hand(int* hand, int* pts, int* numcards);
int end_game(int ppts, int dpts);


///***MAIN***///
int main() {
  
  //attain seed value and SEED FOR ONLY TIME
  printf("Seed: ");
  int seed = 0;
  if (scanf(" %i", &seed) != 1) {
    printf("ERROR: You have to enter an integer seed value.");
    return 1;
  }
  srand(seed);

  //makes a hand for player and dealer
  int* phand = calloc(1, sizeof(int));  //player hand
  int pcards = 0;  //number of cards player has
  int ppts = 0;  //player points
  int* dhand = calloc(1, sizeof(int));  //dealer hand
  int dcards = 0;  //number of cards dealer has
  int dpts = 0; //dealer points

  //goes until a game is played to completion (loops only for push)
  while (1) {
    //creates and shuffles deck
    int deck[52];
    make_deck(deck, seed);
    
    //deals inital two cards for each
    for (int i = 0; i < 2; i++) {
      phand = dealcard(phand, &pcards, &ppts, deck);
      dhand = dealcard(dhand, &dcards, &dpts, deck);
    }
 
    //player plays
    do {
      print_board(phand, dhand, pcards, dcards);
    } while(player_plays(phand, &pcards, &ppts, deck));

    //dealer plays
    print_board(phand, dhand, pcards, -1);  //so does not print asteriks
    while (dealer_plays(dhand, &dcards, &dpts, ppts, deck)) {
      print_board(phand, dhand, pcards, dcards);
    } 

    //if push, reset points and hands
    if (end_game(ppts, dpts) == 2) {  //this is the return value for push
      reset_hand(phand, &ppts, &pcards);
      reset_hand(dhand, &dpts, &dcards);
    }else {  //otherwise finish
      break;
    }
  } //end while


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


  //shuffles deck
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
  
  //check case for start of dealer playing to show second card
  int nostar = 0;
  if (dcards == -1) {
    dcards = 2;
    nostar = 1;
  }

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
    if (dcards == 2 && i == 1 && nostar == 0) {
      printf(" **");
    }else {
      print_value(dfaceval);
      print_suit(dsuitval);
    }
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


int* dealcard(int* hand, int* cards, int* pts, int* deck) {
  
  //takes last card from deck and gives it to hand
  hand[*cards] = deck[51];

  //adds an element to hand and increments num cards
  *cards += 1;
  hand = realloc(hand, (*cards+1) * sizeof(int));
  hand[*cards] = 0;
  
  //updates points
  int tally = 0;
  int aces = 0;
  for (int i = 0; i < *cards; i++) {
    if ((hand[i] % 100) == 14) {
      tally += 1;
      aces += 1;
    }else if ((hand[i] % 100) > 10) {
      tally += 10;
    }else {
      tally += hand[i] % 100;
    }
  }
  //whether ace is 1 or 11
  for (int j = 0; j < aces; j++) {
    if (tally + 10 <= 21) {
      tally += 10;
    }
  }
  *pts = tally;

  //cycles deck so new card next card on top
  for (int k = 0; k < 51; k++) {
    int temp = deck[51];
    deck[51] = deck[k];
    deck[k] = temp;
  }

  return hand;

} //end dealcard


int player_plays(int* phand, int* pcards, int* ppts, int* deck) {
  //prints board/deals until player stands or busts
  char hs;

  //busts
  if (*ppts > 21) {
    printf("Player busts!\n");
    return 0;
  }

  printf("Hit or stand? [h/s] ");
  scanf(" %c", &hs);
  
  //if stand, then print board and go to dealer sequence
  if (hs == 's') {
    return 0;
  }
  
  //deals a card to player
  phand = dealcard(phand, pcards, ppts, deck);

  return 1;

} //end player_plays


int dealer_plays(int* dhand, int* dcards, int* dpts, int ppts, int* deck) {
  
  //dealer sequence
  if (*dpts > 21) {
    printf("Dealer busts!\n");
    return 0;
  }

  //stands if player already busted and have more than 17
  if (ppts > 21 || *dpts >= 17) {
    printf("Dealer stands.\n");
    return 0;
  }
  
  //deals a card to the dealer
  printf("Dealer hits.\n");
  sleep(2);
  dhand = dealcard(dhand, dcards, dpts, deck);
  
  return 1;

} //end dealer_plays


void reset_hand(int* hand, int* pts, int* numcards) {
  //clears hand values
  for (int i = 0; i < *numcards; i++) {
    hand[i] = 0;
  }

  //resets points and card counts
  *pts = 0;
  *numcards = 0;
} //end reset


int end_game(int ppts, int dpts) {
  printf("\nFinal scores: Player %i, Dealer %i.\n", ppts, dpts);
  //player wins if greater than dealer and less than 21 or dealer busts
  if ((ppts > dpts && ppts <= 21) || dpts > 21) {
    printf("Player wins!\n");
    return 0;
  //dealer wins if greater than player and less than 21 or player busts
  }else if ((dpts > ppts && dpts <= 21) || ppts > 21) {
    printf("Dealer wins!\n");
    return 0;
  //need to push because of a tie
  }else {
    printf("Push! Play again.\n");
    return 2;
  }
} //end end_game


