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

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;
using vvvpi = vector<vvpi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, l, n) for (int i = l; i < (n); i++)

#define per(i, n) for (int i = n - 1; i >= 0; i--)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, r, c;

  cin >> n >> r >> c;

  vi a(n);
  rep(i, n) cin >> a[i];

  vvvpi dp(n + 1, vvpi(r, vpi(c + 1, pi(INF, INF))));

  dp[0][0][0] = {0, 0};

  repp(i, 1, n + 1) {
    rep(j, r) {
      rep(k, c + 1) {
        if (dp[i - 1][j][k].first == INF)
          continue;

        if (j + 1 < r) {
          dp[i][j + 1][a[i - 1]] = min(dp[i][j + 1][a[i - 1]], dp[i - 1][j][k]);
        }
        if (a[i - 1] + k <= c) {
          dp[i][j][a[i - 1] + k] = min(dp[i][j][a[i - 1] + k], dp[i - 1][j][k]);
        }

        if (dp[i - 1][j][k].first + 1 < r) {
          dp[i][j][k] = min(dp[i][j][k], {dp[i - 1][j][k].first + 1, a[i - 1]});
        }
        if (dp[i - 1][j][k].second + a[i - 1] <= c) {
          dp[i][j][k] = min(
              dp[i][j][k],
              {dp[i - 1][j][k].first, dp[i - 1][j][k].second + a[i - 1]}
          );
        }
      }
    }
  }

  per(i, n + 1) {
    rep(j, r) {
      rep(k, c + 1) {
        if (dp[i][j][k].first != INF) {
          cout << i << endl;
          return 0;
        }
      }
    }
  }
}
