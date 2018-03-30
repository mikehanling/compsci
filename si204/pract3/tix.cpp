//Mike Hanling
//tix.cpp


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  vector<string> tix;
  string curr;
  int count = 0;
  while (1) {
    cin >> curr;
    
    if (curr == "END") break;

    if (find(tix.begin(), tix.end(), curr) != tix.end()) {
      cout << "Duplicate code: " << curr << endl;
      count++;
    }
    tix.push_back(curr);
  }

  cout << count << " invalid tickets" << endl;

  return 0;
}
