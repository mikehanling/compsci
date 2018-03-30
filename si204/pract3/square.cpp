//Mike Hanling
//square.cpp


#include <iostream>
#include <string>
#include <vector>
using namespace std;


int main() {
  cout << "Size: ";
  int size = 0;
  cin >> size;

  vector< vector<int> > box;

  for (int i = 0; i < size; i++) {
    vector<int> temp;
    for (int k = 0; k < size; k++) {
      int curr;
      cin >> curr;
      temp.push_back(curr);
    }
    box.push_back(temp);
  }

  bool equal = true;

  int checkrow = 0;
  for (int i = 0; i < box.at(0).size(); i++) {
    checkrow += box.at(0).at(i);
  }
  int checkcol = 0;
  for (int i = 0; i < box.size(); i++) {
    checkcol += box.at(i).at(0);
  }

  if (checkrow != checkcol) {
    cout << "Sums do not match" << endl;
    return 0;
  }

  for (int i = 0; i < box.size(); i++) {
    int sumrow = 0;
    int sumcol = 0;
    for (int k = 0; k < box.at(i).size(); k++) {
      sumrow += box.at(i).at(k);
      sumcol += box.at(k).at(i);
    }
    if (sumrow != checkrow || sumcol != checkcol) {
      equal = false;
      break;
    }
  }

  if (!equal) cout << "Sums do not match" << endl;
  else cout << "All sums equal " << checkrow << endl;


  return 0;
}
