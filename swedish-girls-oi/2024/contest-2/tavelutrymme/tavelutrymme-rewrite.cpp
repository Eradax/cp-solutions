#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    EGOI 2024 kvaltävling 2
links:
    https://open.kattis.com/problems/tavelutrymme
*/

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, l, n) for (int i = l; i < (n); i++)

#define per(i, n) for (int i = n - 1; i >= 0; i--)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, r, c;

  cin >> n >> r >> c;

  vi a(n);
  rep(i, n) cin >> a[i];

  vvi dp(n + 1, vi(r * (c + 1), INF));

  dp[0][0] = 0;

  repp(i, 1, n + 1) {
    rep(j, r * (c + 1)) {
      if (dp[i - 1][j] >= INF)
        continue;

      if (j / (c + 1) < r - 1) {
        dp[i][j / (c + 1) * (c + 1) + c + 1 + a[i - 1]] =
            min(dp[i][j / (c + 1) * (c + 1) + c + 1 + a[i - 1]], dp[i - 1][j]);
      }
      if (a[i - 1] + (j % (c + 1)) <= c) {
        dp[i][j + a[i - 1]] = min(dp[i][j + a[i - 1]], dp[i - 1][j]);
      }

      if (dp[i - 1][j] / (c + 1) + 1 < r) {
        dp[i][j] = min(dp[i][j], dp[i - 1][j] + c + 1 + a[i - 1] -
                                     (dp[i - 1][j] % (c + 1)));
      }
      if (dp[i - 1][j] % (c + 1) + a[i - 1] <= c) {
        dp[i][j] = min(dp[i][j], dp[i - 1][j] + a[i - 1]);
      }
    }
  }

  per(i, n + 1) {
    rep(j, r * (c + 1)) {
      if (dp[i][j] < INF) {
        cout << i << endl;
        return 0;
      }
    }
  }
}
