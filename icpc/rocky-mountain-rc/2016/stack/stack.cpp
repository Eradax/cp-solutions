#include <bits/stdc++.h>

#ifdef DBG
#include "../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;
  cin.ignore();

  rep(_, t) {
    string line;
    getline(cin, line);

    int l = sz(line);

    vvi dp(l, vi(l, INF));

    repp(len, 1, l + 1) {
      dbg(len);
      rep(i, l) {
        int j = i + len - 1;
        if (j >= l)
          continue;

        if (i > j) {
          dp[i][j] = 0;
          continue;
        }

        if (i == j) {
          dp[i][j] = 1;
          continue;
        }

        dbg(i, j);

        int ans = 1 + dp[i + 1][j];

        dbg(ans);

        repp(split, i + 1, j + 1) {
          if (line[i] != line[split])
            continue;
          
          int v1 = dp[i][split - 1];
          int v2 = (split + 1 < l && split + 1 <= j ? dp[split + 1][j] : 0);

          dbg(i, split, j, v1, v2);

          ans = min(ans, v1 + v2);
        }

        dbg(ans);

        dp[i][j] = ans;
      }
    }

    rep(i, l) {
      dbg(vi(&dp[i][i], &dp[i][l]));
      // dbg(dp[i]);
    }

    cout << l + 2 * dp[0][l - 1] << endl;
  }
}
