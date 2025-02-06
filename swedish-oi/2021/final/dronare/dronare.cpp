#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ld = long double;
using vld = vector<ld>;
using vvld = vector<vld>;

using vi = vector<int>;
using vvi = vector<vi>;

using v3 = vector<tuple<int, int, int>>;

#define rep(i, n) for (int i = 0; i < (n); i++)

/*
for a certain time we can determine wether or not it's possible with a knapsack
=>
solve by binary searching over time
*/

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, b, W;
  cin >> n >> b >> W;

  v3 bat(n);

  rep(i, n) {
    int a, b, c;
    cin >> a >> b >> c;
    bat[i] = {a, b, c};
  }

  ld lo = 0;
  ld hi = 1e9;

  rep(_, 50) {
    ld mi = lo + (hi - lo) / 2;

    vvld dp(n + 1, vld(b + 1));

    rep(i, n + 1) {
      rep(w, b + 1) {
        if (i == 0) {
          dp[i][w] = 0;
        } else {
          auto [e1, w1, c1] = bat[i - 1];
          int cost = c1;
          ld val = (ld)e1 - mi * (ld)w1;

          if (cost <= w) {
            dp[i][w] = max(dp[i - 1][w - cost] + val, dp[i - 1][w]);
          } else {
            dp[i][w] = dp[i - 1][w];
          }
        }
      }
    }

    if (dp[n][b] > mi * (ld)W) {
      lo = mi;
    } else {
      hi = mi;
    }
  }

  cout << setprecision(15) << (lo + hi) / 2 << endl;
}
