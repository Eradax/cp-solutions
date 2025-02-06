#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:
    Northwestern Europe Regional Contest (NWERC) 2017
links:
    https://open.kattis.com/problems/installingapps
*/

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, c;
  cin >> n >> c;

  vi d(n), s(n);
  vector<pair<int, int>> v(n);
  vi vtoi(n);

  rep(i, n) {
    cin >> d[i] >> s[i];
    v[i] = {s[i] - d[i], i};
  }

  sort(v.begin(), v.end());

  rep(i, n) {
    vtoi[v[i].second] = i;
  }

  dbg(v);

  // dp[i][j] = minimal downloaded size to choose j out of the first i apps
  vvi dp(n, vi(n + 1, -2));
  vvi p(n + 1, vi(n + 1, -2));

  rep(i, n) {
    rep(j, n + 1) {
      int idx = v[i].second;

      if (j == 0) {
        dp[i][j] = 0;
        p[i][j] = -1;
      } else if (i + 1 < j) {
        dp[i][j] = INF;
        p[i][j] = -1;
      } else if (i == 0) {
        dp[i][j] = (max(d[idx], s[idx]) <= c) ? s[idx] : INF;  // j == 1
        p[i][j] = (max(d[idx], s[idx]) <= c) ? idx : -1;
      } else {
        int v1, v2;
        v1 = dp[i - 1][j];
        v2 = (dp[i - 1][j - 1] + max(d[idx], s[idx]) <= c)
                 ? dp[i - 1][j - 1] + s[idx]
                 : INF;
        if (v1 <= v2) {
          dp[i][j] = v1;
          p[i][j] = p[i - 1][j];
        } else {
          dp[i][j] = v2;
          p[i][j] = idx;
        }
      }
    }
  }

  rep(i, n) {
    dbg(dp[i]);
  }

  rep(i, n) {
    dbg(p[i]);
  }

  int i = n - 1;
  int j = n;

  while (dp[i][j] == INF)
    j--;

  cout << j << endl;

  vi ans;

  while (j > 0 && i >= 0) {
    ans.emplace_back(p[i][j] + 1);
    i = vtoi[p[i][j]] - 1;
    j--;
  }

  reverse(ans.begin(), ans.end());

  for (auto& e : ans) {
    cout << e << " ";
  }
  cout << endl;
}
