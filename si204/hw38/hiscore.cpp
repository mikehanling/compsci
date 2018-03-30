//Mike Hanling
//hiscore.cpp


#include <iostream>
#include <string>
#include <vector>
using namespace std;


struct result {
  string name;
  int score;
};


istream& operator>> (istream& in, result& res);
bool operator< (result a, result b);
ostream& operator<< (ostream& out, result res);


int main() {
  int n = 5;
  cout << "Enter " << n << " results:" << endl;
  vector<result> res;

  for (int i=0; i < n; ++i) {
    result temp;
    cin >> temp;
    res.push_back(temp);
  }

  // find highest score
  result best = res[0];
  for (int i=1; i < res.size(); ++i) {
    if (best < res[i]) {
      best = res[i];
    }
  }

  // print highest score
  cout << "The best result is " << best << endl;

  return 0;
}


istream& operator>> (istream& in, result& res) {
  in >> res.name >> res.score;
  return in;
}

bool operator< (result a, result b) {
  return a.score < b.score;
}

ostream& operator<< (ostream& out, result res) {
  out << res.name << " (" << res.score << " points)" << endl;
  return out;
}
