//Mike Hanling
//longword.c

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
  cout << "Enter words and then STOP:" << endl;
  
  vector<string> words;
  string curr;
  while (curr != "STOP") {
    cin >> curr;
    words.push_back(curr);
  }

  int longest = 0;
  for (int i = 0; i < words.size(); i++) {
    if (words[i].length() > longest) {
      longest = words[i].length();
      curr = words[i];
    }
  }

  cout << "The longest word is " << curr << endl;

  return 0;
}
