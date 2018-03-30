/*   Generic Functions   */

//These are basic functions that be reused again
//with minimal changes

//Remember to check types of parameters and subfunction definition



//SelectionSort   (uses "before")
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

//this is make array sorted greatest to least
int before(int a, int b) {
  return a > b;
}


//Search Function   (uses "match")
int search(double* data, int size, double x) {
  int i = 0;
  while(i < size && !match(data[i], x)) {
    i++;
  }
  return i;
}

//matches doubles within .1 of each other
int match(double a, double b) {
  double diff = a - b;
  return diff > -0.1 && diff < 0.1;
}
