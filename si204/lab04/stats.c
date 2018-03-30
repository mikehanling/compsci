#include "si204.h"

int main() {
  
  //get filename and column header from user
  fprintf(stdout, "Filename: ");
  cstring filename;
  fscanf(stdin, "%s", filename);
  fprintf(stdout, "Column heading: ");
  cstring column;
  fscanf(stdin, "%s", column);
  
  stream fin = fopen(filename, "r");

  
  int colcount = 0;  //column that is being checked
  int statcol = 0;  //column number of desired stat
  cstring currentcol;
  
  //find column number of desired header
  fscanf(fin, " %s", currentcol);
  while (strcmp(currentcol, "1") != 0) {
    fscanf(fin, " %s", currentcol);
    colcount++;
    if (strcmp(currentcol, column) == 0) {
      statcol = colcount;
    }
  }


  cstring team, team2, team3;  //team name, second or third word place holder
  cstring teamtop;  //team with highest stat
  double junk;  //used to pass values through
  double stat = 0;  //desired stat value
  double stattop = 0;  //highest stat
  

  // out for loop is to run through line by line
  for (int i = 0; i < 30; i++) {
    
    //take in the only string (team) first
    fscanf(fin, " %s", team);
    //check for team name of multiple words (hardcoded for 76ers issue)
    while (fscanf(fin, " %lg", &junk) == 0 || junk == 76.0) {
      if (junk == 76.0) {
        fscanf(fin, " %s", team3);
        sprintf(team2, "%.2ge%s", junk, team3);
      }else {
        fscanf(fin, "%s", team2);
        strcat(team, " ");
        strcat(team, team2);
      }
    }
    
    //read in all the stats, saving the desired stat
    for (int j = 0; j <= (colcount); j++) {
      //this is because the above if statement will read in the first stat
      if (j != 0) {
        fscanf(fin, " %lg", &junk);
      }
      if (j == (statcol-2)) {
        stat = junk;
      }
    }
    
    //check for higher stat value and update as necessary
    if (stat > stattop) {
      stattop = stat;
      strcpy(teamtop, team);
    }
  }
  fclose(fin);

  //print out the team name and value which was largest
  fprintf(stdout, "%s %g\n", teamtop, stattop);

  return 0;
}
