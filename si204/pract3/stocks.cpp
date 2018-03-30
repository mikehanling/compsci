//Mike Hanling
//stocks.cpp


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;


struct stock{
  string name;
  double pps;
  double ns;
  double te;
  double pe;
};


int main() {
  cout << "Filename: ";
  string file;
  cin >> file;
  ifstream fin(file.c_str());

  int numstock = 0;
  fin >> numstock;
  
  string junk;
  fin >> junk >> junk >> junk >> junk;

  vector<stock> stocks;
  for (int i = 0; i < numstock; i++) {
    stock temp;
    fin >> temp.name >> temp.pps >> temp.ns >> temp.te;
    temp.pe = temp.pps * temp.ns / temp.te;
    stocks.push_back(temp);
  }

  sort(stocks.begin(), stocks.end());

  for (int i = 0; i < numstock; i++) {
    cout << stocks.at(i).name << " " << stocks.at(i).pe << endl;
  }

  return 0;
}


bool operator< (stock a, stock b) {
  return b.pe < a.pe;
}
