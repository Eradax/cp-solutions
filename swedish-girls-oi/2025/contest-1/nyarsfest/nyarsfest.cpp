#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:

links:
    https://egoi25-qual.kattis.com/contests/egoi25-jul/problems/nyarsfest
*/

using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  cout << n * (m + 1) << endl;
}
