//Mike Hanling
//large.c


#include <stdio.h>
#include <stdlib.h>


typedef struct {
  int ID;
  double timedelay;
  char* IPsource;
  char* IPdest;
  char* protocol;
  int bytes;
} conn;


conn read_oneConnection(conn* allconnptr, int numconn, FILE* file);
void selectionSort(int* data, int size);
int before(int , int b);



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

  //make array of byte sizes
  int* connbytes = calloc(numconn, sizeof(int));
  for (int i = 0; i < numconn; i++) {
    connbytes[i] = allconn[i].bytes;
  }

  //sort the byte sizes
  selectionSort(connbytes, numconn);

  //print the biggest ten
  for (int i = 0; i < 10; i++) {
    printf("%i\n", connbytes[i]);
  }

  free(connbytes);
  free(allconn);
  return 0;
}


conn read_oneConnection(conn* allconnptr, int numconn, FILE* file) {
  //read in all attributes of one connection
  int ID;
  double timedelay;
  char IPsource[128];
  char IPdest[128];
  char protocol[128];
  int bytes;
  fscanf(file, " %i %lg %s %s %s %i", &ID, &timedelay, IPsource, IPdest, protocol, &bytes);

  //make the "conn"
  conn dataout = {ID, timedelay, IPsource, IPdest, protocol, bytes};

  return dataout;


}


void selectionSort(int* data, int size) {
  for(int length = size; length > 1; --length) {
    // Find imax, the index of the largest
    int imax = 0;
    for(int i = 1; i < length; ++i) {
      if (before(data[imax], data[i])) {
        imax = i;
      }
    }
    // Swap data[imax] & the last element
    int temp = data[imax];
    data[imax] = data[length - 1];
    data[length - 1] = temp;
  }
}
int before(int a, int b) {
  return a > b;
}

