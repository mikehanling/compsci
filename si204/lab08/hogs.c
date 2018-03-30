//Mike Hanling
//hogs.c


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

typedef struct {
  char* IP;
  int totalbytes;
} source;


conn read_oneConnection(conn* allconnptr, int numconn, FILE* file);
void selectionSort_string(char** data, int* shadowData, int size);
void selectionSort_num(int* data, char** shadowData, int size);
int stringbefore(char* a, char* b);
int numbefore(int a, int b);
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

  //make array of IP source names and byte sizes
  char** connSources = calloc(numconn, sizeof(char*));
  int* connBytes = calloc(numconn, sizeof(int));
  for (int i = 0; i < numconn; i++) {
    connSources[i] = calloc(128, sizeof(char));
    strcpy(connSources[i], allconn[i].IPsource);
    
    connBytes[i] = allconn[i].bytes;
  }

  //sort IP sources in alphabetical order (shadow sort the bytes)
  selectionSort_string(connSources, connBytes, numconn);
  
  //find how many different IPs are present
  int diffIPs = numDistinct(connSources, numconn);
  
  //create array of IP and total byte size for each
  char** IPs = calloc(diffIPs, sizeof(char*));
  for (int i = 0; i < diffIPs; i++) {
    IPs[i] = calloc(128, sizeof(char));
  }
  int numIPs = 0;
  int* totalbytes = calloc(diffIPs, sizeof(int));

  //add each new IP and sum byte sizes along the way
  strcpy(IPs[0], connSources[0]);
  for (int i = 0; i < numconn; i++) {
    if (strcmp(IPs[numIPs], connSources[i]) != 0) {
      numIPs++;
      strcpy(IPs[numIPs], connSources[i]);
    }
    totalbytes[numIPs] += connBytes[i];
  }
  //sort bytes greatest to least (shadow sort the IPs)
  selectionSort_num(totalbytes, IPs, diffIPs);

  //print the top ten IPs
  for (int i = 0; i < 10; i++) {
    if (i == diffIPs) break;  //if the file has less than 10 IPs
    printf("%s\n", IPs[i]);
  }

  //free
  for (int i = 0; i < numconn; i++) {
    if (i < diffIPs) {
      free(IPs[i]);
    }
    free(connSources[i]);
  }
  free(connSources);
  free(connBytes);
  free(IPs);
  free(totalbytes);
  free(allconn);

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


void selectionSort_string(char** data, int* shadowData, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (stringbefore(data[imax], data[i])) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    char* stemp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = stemp;

    //do same swap for shadowData
    int ntemp = shadowData[imax];
    shadowData[imax] = shadowData[length - 1];
    shadowData[length - 1] = ntemp;
  }
}
int stringbefore(char* a, char* b) {
  return strcmp(a, b) < 0;
}


void selectionSort_num(int* data, char** shadowData, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (numbefore(data[imax], data[i])) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    int ntemp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = ntemp;

    //do same swap for shadowData
    char* stemp = shadowData[imax];
    shadowData[imax] = shadowData[length - 1];
    shadowData[length - 1] = stemp;
  }
}
int numbefore(int a, int b) {
  return a > b;
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
