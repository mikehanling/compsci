//Mike Hanling
//
//extra.c
//
//seed of 0 no longer is an shuffled deck
//
//deck is made by shuffling seven decks together
//
//player/dealer with blackjack instantly wins (push for dealer and player)
//
//can play with as many people as you want (or as much as memory can hold)
//
//initial balance with beting is tracked (up to the players to monitor how much
//                                 they have, reports balances after each hand)


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


///***PROTOTYPES***///
void make_deck(int* deck);
void print_board(int** phands, int* dhand, 
                 int* pcards, int dcards, 
                 int numplayers, char** names);
void print_value(int facevalue);
void print_suit(int suitvalue);
int* dealcard(int* hand, int* cards, int* pts, int* deck);
int player_plays(int* phand, int* pcards, int* ppts, int *deck, char* name);
int dealer_plays(int* dhand, int* dcards, int* dpts, int* ppts, 
                 int* deck, int numplayers);
void display_balances(int** balances, int numplayers, char** names);
void reset_hand(int* hand, int* pts, int* pcards);
int end_game(int* ppts, int dpts, int numplayers, char** names, int** balances);


///***MAIN***///
int main() {
  
  //attain seed value and SEED FOR ONLY TIME
  printf("Seed: ");
  int seed = 0;
  if (scanf(" %i", &seed) != 1) {
    printf("ERROR: must be an integer value for seed");
    return 1;
  }
  srand(seed);

  //creates and shuffles deck
  int deck[7*52];
  make_deck(deck);

  //ask for initial inputs
  int numplayers = 0;
  printf("Number of player: ");
  scanf(" %i", &numplayers);
  
  //keep all of the names
  char** names = calloc(numplayers, sizeof(char*));
  //each player has two ints: balance and bet
  int** balances = calloc(numplayers, sizeof(int*));

  //storage for all player hands
  int** phands = calloc(numplayers, sizeof(int*));  //player hands
  int* pcards = calloc(numplayers, sizeof(int));  //number of cards player has
  int* ppts = calloc(numplayers, sizeof(int));  //player points
  
  char thisname[128];
  for (int i = 0; i < numplayers; i++) {
    printf("Player %i name: ", i+1);
    scanf(" %s", thisname);
    names[i] = calloc(strlen(thisname), sizeof(char));
    strcpy(names[i], thisname);

    balances[i] = calloc(2, sizeof(int));
    printf("Amount %s is playing with: $", names[i]);
    scanf(" %i", &balances[i][0]);

    //creates hand
    phands[i] = calloc(12, sizeof(int)); //largest hand size possible
    pcards[i] = 0;
    ppts[i] = 0;

    printf("\n");
  }

  //creates dealer hand
  int* dhand = calloc(1, sizeof(int));  //dealer hand
  int dcards = 0;  //number of cards dealer has
  int dpts = 0; //dealer points

  printf("We will be playing Blackjack. Bets are made before dealing."
         "Minimum bet is $5. Pay out will be 2:1.\n");

  //goes until a game is played to completion (loops only for push)
  int playon = 1;
  while (playon) {
    //take bets
    int bet = 0;
    for (int i = 0; i < numplayers; i++) {
      printf("\n%s, how much do you bet? $", names[i]);
      scanf(" %i", &bet);
      balances[i][1] = bet;
      balances[i][0] -= bet;
    }

    //deals inital two cards for each
    int blackjack = 0;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < numplayers; j++) {
        phands[j] = dealcard(phands[j], &pcards[j], &ppts[j], deck);
      }
      dhand = dealcard(dhand, &dcards, &dpts, deck);

      //check for blackjack
      if (ppts[i] == 21 || dpts == 21) {
        blackjack++;
      }
    }

    //ends game is anyone got blackjack
    if (blackjack) {
      end_game(ppts, dpts, numplayers, names, balances);
    }

    //players play
    for (int j = 0; j < numplayers; j++) {
      do {
        print_board(phands, dhand, pcards, dcards, numplayers, names);
      }while(player_plays(phands[j], &pcards[j], &ppts[j], deck, names[j]));
    }

    //dealer plays (-1 so that the asteriks are not printed)
    print_board(phands, dhand, pcards, -1, numplayers, names);
    while(dealer_plays(dhand, &dcards, &dpts, ppts, deck, numplayers)) {
      print_board(phands, dhand, pcards, dcards, numplayers, names);
    }

    //if not push, ask to play again
    if (end_game(ppts, dpts, numplayers, names, balances) != 2) {
      display_balances(balances, numplayers, names);
      char yesno;
      printf("\nPlay again? [y/n] ");
      fflush(stdout);
      scanf(" %c", &yesno);
      if (yesno == 'n') {
        playon = 0;
      }
    }
    
    //reset hands
    for (int j = 0; j < numplayers; j++) {
      reset_hand(phands[j], &ppts[j], &pcards[j]);
      balances[j][1] -= balances[j][1];
    }
    reset_hand(dhand, &dpts, &dcards);

  } //end while

  printf("Thanks for playing!\n\n");

  //set 'em free
  for (int i = 0; i < numplayers; i++) {
    free(phands[i]);
    free(names[i]);
    free(balances[i]);
  }
  free(phands);
  free(names);
  free(balances);
  free(pcards);
  free(ppts);
  free(dhand);
  return 0;
} //end main


///***FUNCTIONS DEFS***///
void make_deck(int* deck) {
  
  //create unshuffled deck
  int faceval = 2;
  int suitval = 1;
  for (int i = 0; i < (7*52); i++) {  //hard coded 52 because every deck is same
    deck[i] = (100*suitval) + faceval;
    faceval++;
    if (faceval % 15 == 0) {
      faceval = 2;
      suitval++;
      if (suitval > 4) {
        suitval = 1;
      } //end if
    } //end if

  } //end for
  
  
  //shuffles deck
  for (int swap1 = 0; swap1 < (7*52); swap1++) {
    int swap2 = rand() % (7*52);
    int temp = deck[swap1];
    deck[swap1] = deck[swap2];
    deck[swap2] = temp;
  }

  
  //returns shuffled deck
  return;

} //end make_deck


void print_board(int** phands, int* dhand, 
                 int* pcards, int dcards, 
                 int numplayers, char** names) 
{
  printf("\n");

  //check case for start of dealer playing to show second card
  int nostar = 0;
  if (dcards == -1) {
    dcards = 2;
    nostar = 1;
  }

  //determines longest hand and prints names
  int cards = 0;
  for (int i = 0; i < numplayers; i++) {
    if (pcards[i] > cards) {
      cards = pcards[i];
    }
    printf("%7s", names[i]);
  }
  if (dcards > cards) {
    cards = dcards;
  }
  printf(" Dealer\n");

  //players
  //for every "card" in longest hand
  for (int i = 0; i < cards; i++) {
    //for each player
    for (int j = 0; j < numplayers; j++) {
      //decodes the face and suit values
      //player
      int pfaceval = phands[j][i] % 100;
      int psuitval = phands[j][i] / 100;

      printf("| ");

      //prints the correct face value and suit char for player
      print_value(pfaceval);
      print_suit(psuitval);

      printf("  ");
    } //end each player

    printf("| ");
    //dealer
    int dfaceval = dhand[i] % 100;
    int dsuitval = dhand[i] / 100;
    
    if (dcards == 2 && i == 1 && nostar == 0) {
      printf (" **");
    }else {
      //prints the correct face value and suit char for dealer
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
  hand[*cards] = deck[(7*52)-1];
      
  //adds an element to hand and increments num cards
  *cards += 1;
  
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
  for (int k = 0; k < ((7*52)-1); k++) {
    int temp = deck[(7*52)-1];
    deck[(7*52)-1] = deck[k];
    deck[k] = temp;
  }

  return hand;

} //end dealcard


int player_plays(int* phand, int* pcards, int* ppts, int* deck, char* name) {
  //prints board/deals until player stands or busts
  char hs;

  //busts
  if (*ppts > 21) {
    printf("%s busts!\n", name);
    return 0;
  }

  printf("%s, Hit or stand? [h/s] ", name);
  scanf(" %c", &hs);
  
  //if stand, then print board and go to dealer sequence
  if (hs == 's') {
    return 0;
  }
  
  //deals a card to player
  phand = dealcard(phand, pcards, ppts, deck);

  return 1;

} //end player_plays


int dealer_plays(int* dhand, int* dcards, int* dpts, int* ppts, 
                 int* deck, int numplayers) 
{  
  //see if all players busted
  int playersin = numplayers;
  for (int i = 0; i < numplayers; i++) {
    if (ppts[i] > 21) {
      playersin--;
    }
  }
  //dealer sequence
  if (*dpts > 21) {
    printf("Dealer busts!\n");
    return 0;
  }

  //stands all players busted and have more than 17
  if (playersin == 0 || *dpts >= 17) {
    printf("Dealer stands.\n");
    return 0;
  }

  //deals a card to dealer
  printf("Dealer hits.\n");
  sleep(2);
  dhand = dealcard(dhand, dcards, dpts, deck);
  
  return 1;

} //end dealer_plays


void display_balances(int** balances, int numplayers, char** names) {
  printf ("\nFinal balances:\n");
  for (int i = 0; i < numplayers; i++) {
    printf("%7s $%i\n", names[i], balances[i][0]);
  }
} //end display_balances

void reset_hand(int* hand, int* pts, int* numcards) {
  //clears hand values
  for (int i = 0; i < *numcards; i++) {
    hand[i] = 0;
  }

  //resets points and card counts
  *pts = 0;
  *numcards = 0;
} //end reset


int end_game(int* ppts, int dpts, int numplayers, char** names, int** balances) {
  int winner;
  int highest = 0;
 
  //finds highest score below 21
  printf ("\nFinal scores:\n");
  for (int i = 0; i < numplayers; i++) {
    if (ppts[i] > highest && ppts[i] <= 21) {
      highest = ppts[i];
      winner = i;
    }
    printf("%7s %i\n", names[i], ppts[i]);
  }
  printf(" Dealer %i\n", dpts);

  //player wins if greater than dealer and less than 21
  if (highest > dpts || dpts > 21) {
    printf("%s wins!\n", names[winner]);

    //payout (2:1)
    balances[winner][0] += 2 * balances[winner][1];
    for (int i = 0; i < numplayers; i++) {
      if (ppts[i] == highest && i != winner) {
        printf ("%s wins!\n", names[i]);
        balances[i][0] += 2 * balances[i][1];  //this is the bet
      }
    }
    return 0;

  //dealer wins if greater than player and less than 21 or player busts
  }else if ((dpts > highest && dpts <= 21) || highest == 0) {
    printf("Dealer wins!\n");
    return 0;
  //need to push because of a tie
  }else {
    printf("Push! Play again.\n");
    //give money back to balance since no one won
    for (int i = 0; i < numplayers; i++) {
      balances[i][0] += balances[i][1];
    }
    return 2;
  }
} //end end_game


