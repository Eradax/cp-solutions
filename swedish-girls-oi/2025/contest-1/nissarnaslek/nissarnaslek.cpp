#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    
links:
    https://egoi25-qual.kattis.com/contests/egoi25-jul/problems/nissarnaslek
*/

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  int n;
  cin >> n;
  rep(i, n) {
    string word;
    cin >> word;
    word[0] = 'a' + (word[0] == 'a');
    cout << word << endl << flush; 
  }
}
