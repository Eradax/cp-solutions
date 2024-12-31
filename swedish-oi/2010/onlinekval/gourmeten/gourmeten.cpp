#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    Programmeringsolympiadens onlinekval 2010
links:
    https://open.kattis.com/problems/gourmeten
*/

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int dp[1010];

int main() {
  int m;
  cin >> m;

  int n;
  cin >> n;

  vector<int> t(n);
  rep(i, n) { cin >> t[i]; }

  dp[0] = 1;

  rep(i, m + 1) {
    rep(j, n) {
      int v = t[j] + i;

      if (v < 1010)
        dp[v] += dp[i];
    }
  }

  cout << dp[m] << endl;
}
