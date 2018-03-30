#include "si204.h"

int main() {
  
  //set up optional initial conditions
  double initbal = 0.0;
  double paycheck = 0.0;
  double saverate = 0.0;
  double loanrate = 0.0;
  cstring trash;
  
  //read in init balance, paycheck, rate, or command
  cstring command;
  readstring(command, stdin);
  
  //check for initbal, paycheck, or rate in any order
  while (strcmp(command, "run") != 0) {
    if (strcmp(command, "paycheck") == 0) {
      readstring(trash, stdin);
      paycheck = readnum(stdin);
    }else if (strcmp(command, "initbal") == 0) {
      readstring(trash, stdin);
      initbal = readnum(stdin);
    }else if (strcmp(command, "saverate") == 0) {
      readstring(trash, stdin);
      saverate = readnum(stdin);
    }else if (strcmp(command, "loanrate") == 0) {
      readstring(trash, stdin);
      loanrate = readnum(stdin);
    }else {  
      //makes sure that at least a valid initial was given
      //if it is not, then it will break and catch the next if block
      break;
    }
    //reset command string to check for multiple conditions
    readstring(command, stdin);
  }

  //if nonsense run commmand, throw error and return 1  
  if (strcmp(command, "run") != 0) {
    fputs("Invalid command: ", stdout);
    fputs(command, stdout);
    fputc('\n', stdout);
    return 1;
  }

  //read in fileaname
  cstring filename;
  readstring(filename, stdin);
  stream fin = fopen(filename, "r");
  
  //if filename does no exist: throw error and return 2
  if (fin == NULL) {
    fputs("File \"", stdout);
    fputs(filename, stdout);
    fputs("\" not found!", stdout);
    fputc('\n', stdout);
    return 2;
  }
  
  //set up variables needed for daily update
  int days = readnum(fin);   //total number of days of transactions
  readstring(trash, fin);    //reads through "days"
  cstring type;              //categorizes deposit vs withdrawal
  double trans = 0.0;        //specific transaction amount
  double balance = initbal;  //is 0 if never given initbal
  double dbal = 0.0;         //daily balance (to be dividend in average)
  double side = 0.0;         //starts side account for interest/debt


  ///**************///
  ///*DAILY UPDATE*///
  ///**************///
  for (int i = 0; i < days; ++i) {
    
    /*Initial Conditions*/
    
    //calculate interest and update balance every 30 days
    if (balance > 0) {
      side += (balance*(saverate/100));
    }else {
      side += (balance*(loanrate/100));
    }
    if ((i+1)%30 == 0) {
      balance += side;
      side = 0.0;
    }
    
    //input paycheck if every other friday (4th, not 11th, 18th,...)
    if (i%7 == 4 && i%2 == 0) {
      balance += paycheck;
    }
    
    /*Transactions*/

    readstring(type, fin);
    
    //run transactions until end of day, then go on to next day 
    while (strcmp(type, "ENDOFDAY") != 0) {
      trans = readnum(fin);
      //if withdrawal, then change transaction amt to negative
      if (strcmp(type, "W") == 0) {
        trans = trans*-1;
      }
      balance += trans;
      readstring(type, fin);
    }
    dbal += balance;  //this only needs to be updated once a day
  }
  fclose(fin);


  //Output info back to user
  fputs("Simulated ", stdout);
  writenum(days, stdout);
  fputs(" days.\n", stdout);
  fputs("Final balance: ", stdout);
  writenum(balance, stdout);
  fputs("\nAverage end-of-day balance: ", stdout);
  writenum(dbal/days, stdout);
  //fputc('\n', stdout);

  return 0;
}
