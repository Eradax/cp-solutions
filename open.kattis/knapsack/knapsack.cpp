#include <bits/stdc++.h>
#include <bitset>

#ifdef DBG
#include "../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    KTH CSC Popup 2006
links:
    https://open.kattis.com/problems/knapsack
*/

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);
  while (true) {
    int c, n;
    cin >> c >> n;

    if (c == 0 || n == 0)
      break;

    dbg(c, n);

    vi v(n), w(n);
    vector<vector<pair<int, bool>>> dp(n + 1, vector<pair<int, bool>>(c + 1));

    rep(i, n) { cin >> v[i] >> w[i]; }

    dbg(v, w);

    rep(i, n + 1) {
      rep(j, c + 1) {
        if (i && j) {
          if (w[i - 1] <= j) {
            dbg(i - 1, j - w[i - 1]);

            int v1, v2;
            v1 = v[i - 1] + dp[i - 1][j - w[i - 1]].first;
            v2 = dp[i - 1][j].first;

            dp[i][j] = {max(v1, v2), v1 > v2};
          } else {
            dp[i][j] = {dp[i - 1][j].first, 0};
          }
        } else {
          dp[i][j] = {0, 0};
        }
      }
    }

    dbg(dp);

    int ans = 0;
    vi anss;

    while (c > 0 && n > 0) {
      auto [a, b] = dp[n][c];

      dbg(n, c, a, b);

      n -= 1;
      if (b)
        c -= w[n];

      ans += b;
      if (b)
        anss.emplace_back(n);
    }

    cout << ans << '\n';
    rep(i, ans) { cout << anss[i] << ' '; }
    cout << '\n';
  }
}
