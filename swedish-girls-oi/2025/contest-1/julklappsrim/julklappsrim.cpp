#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:

links:
    https://egoi25-qual.kattis.com/contests/egoi25-jul/problems/julklappsrim
*/

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  bool c = 0, h = 0;

  rep(i, n) {
    string word;
    cin >> word;
    c |= word == "snabb";
    h |= word == "varm";
  }

  if (c ^ h) {
    cout << (c ? "cykel" : "halsduk") << endl;
  } else {
    cout << "vet inte" << endl;
  }
}
