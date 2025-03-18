// #pragma GCC optimize("Ofast")
// #include <bitset>
// #pragma GCC target("avx2")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define perr(i, s, n) for (int i = n - 1; i >= s; i--)
#define per(i, n) perr(i, 0, n)

#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

using ll = long long;
#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static constexpr int INF = 1e18;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, t;
  cin >> n >> m >> t;

  assert(n <= 100 && t <= 100);

  vvpi adj(n);
  vi par(n);

  rep(_, n - 1) {
    int a, b, ti;
    cin >> a >> b >> ti;
    adj[a].emplace_back(b, ti);
    adj[b].emplace_back(a, ti);
  }

  {
    function<void(int, int)> dfs = [&](int u, int p) {
      par[u] = p;

      for (auto [v, _] : adj[u]) {
        if (v == p)
          continue;
        dfs(v, u);
      }
    };
    dfs(0, -1);
  }

  vi energy(n);
  repp(i, 1, n) cin >> energy[i];

  vi rats(m);
  vi ratsat(n, -1);
  rep(i, m) {
    cin >> rats[i];
    ratsat[rats[i]] = i;
  }

  dbg(adj);
  dbg(par);

  vvi dp(n, vi(t + 1, -1));
  function<int(int, int)> dfs = [&](int u, int t) -> int {
    dbg(u, t);

    if (t < 0) {
      dbg(0);
      return 0;
    }

    if (t == 0) {
      dbg(0);
      dp[u][t] = 0;
      return 0;
    }

    if (ratsat[u] != -1) {
      dbg(t * energy[u]);
      dp[u][t] = t * energy[u];
      return t * energy[u];
    }

    if (sz(adj[u]) <= 1 && par[u] != -1) {
      dp[u][t] = 0;
      return 0;
    }

    if (dp[u][t] != -1) {
      dbg(dp[u][t]);
      return dp[u][t];
    }

    int ans = INF;

    if (u != 0)
      ans = min(ans, dfs(u, t - 1) + energy[u]);

    {
      int tmp = 0;
      int cnt = 0;
      for (auto [v, w] : adj[u]) {
        if (v == par[u])
          continue;

        cnt++;
        tmp += dfs(v, t - w);
      }

      if (cnt)
        ans = min(ans, tmp);
    }

    dbg(u, ans);

    return dp[u][t] = ans;
  };

  cout << dfs(0, t) << endl;

  // check for determining convex
  // rep(i, n) rep(j, t + 1) dfs(i, j);
  //
  // for (auto row : dp) {
  //   dbg(row);
  //
  //   unordered_set<int> slopes;
  //
  //   rep(i, sz(row)-1) {
  //     cout << row[i] - row[i+1] << " \n"[i==sz(row)-2];
  //
  //     slopes.insert(row[i] - row[i+1]);
  //   }
  //
  //   rep(i, sz(row) - 2) {
  //     assert(2* row[i+1] <= row[i] + row[i+2]);
  //   }
  //
  //   dbg(sz(slopes));
  // }
}
