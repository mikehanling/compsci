//Mike Hanling
//distinct.c


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
  int ID;
  double timedelay;
  char* IPsource;
  char* IPdest;
  char* protocol;
  int bytes;
} conn;


conn read_oneConnection(conn* allconnptr, int numconn, FILE* file);
void selectionSort(char** data, int size);
int before(char* a, char* b);
int numDistinct(char** data, int size);


int main() {
  //get filename and open
  printf("What file? ");
  char filename[128];
  scanf(" %s", filename);
  FILE* fin = fopen(filename, "r");

  //read in num connections
  int numconn = 0;
  fscanf(fin, " %i", &numconn);

  //array to hold all connection
  conn* allconn = calloc(numconn, sizeof(conn));

  //read in all file data (connections)
  for (int i = 0; i < numconn; i++) {
    allconn[i] = read_oneConnection(allconn, numconn, fin);
  }


  //make array of protocol names
  char** connprot = calloc(numconn, sizeof(char*));
  for (int i = 0; i < numconn; i++) {
    connprot[i] = calloc(128, sizeof(char));
    strcpy(connprot[i], allconn[i].protocol);
  }

  //sort in alphabetical order
  selectionSort(connprot, numconn);

  //find how many different protocols are present
  int diffprot = numDistinct(connprot, numconn);

  //print out to user
  printf("%i\n", diffprot);


  return 0;
}


conn read_oneConnection(conn* allconnptr, int numconn, FILE* file) {
  //read in all attributes of one connection
  int ID;
  double timedelay;
  char* IPsource = calloc(128, sizeof(char));
  char* IPdest = calloc(128, sizeof(char));
  char* protocol = calloc(128, sizeof(char));
  int bytes;
  fscanf(file, " %i %lg %s %s %s %i", &ID, &timedelay, IPsource, IPdest, protocol, &bytes);

  //make the "conn"
  conn dataout = {ID, timedelay, IPsource, IPdest, protocol, bytes};

  return dataout;
}


void selectionSort(char** data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (before(data[imax], data[i])) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    char* temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}
int before(char* a, char* b) {
  return strcmp(a, b) < 0;
}


int numDistinct(char** data, int size) {
  int ans = 1;
  for (int i = 0; i < size-1; i++) {
    if (strcmp(data[i], data[i+1]) != 0) {
      ans++;
    }
  }
  return ans;
}
