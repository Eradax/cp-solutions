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
static constexpr int N = 100;
static constexpr int T = 100;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, t;
  cin >> n >> m >> t;

  assert(n <= 100 && t <= 100);

  vvpi adj(n);
  vi par(n);
  vi dists(n);
  vi dist0(n);
  vi end(n);

  rep(_, n - 1) {
    int a, b, ti;
    cin >> a >> b >> ti;
    adj[a].emplace_back(b, ti);
    adj[b].emplace_back(a, ti);
  }

  {
    function<void(int, int)> dfs;
    dfs = [&](int u, int p) {
      for (auto [v, w] : adj[u]) {
        if (v == p)
          continue;
        dist0[v] = w + dist0[u];
        dfs(v, u);
      }
    };
    dfs(0, -1);
  }

  {
    int e;

    function<void(int, int)> dfs;
    dfs = [&](int u, int p) {
      end[u] = e;
      par[u] = p;
      for (auto [v, w] : adj[u]) {
        if (v == p)
          continue;
        dists[v] = w + dists[u];
        dfs(v, u);
      }
    };

    par[0] = -1;

    for (auto [u, w] : adj[0]) {
      e = u;
      dists[u] = 0;
      dfs(u, 0);
    }
  }

  dbg(end);
  dbg(dist0);
  dbg(adj, par);
  dbg(dists);

  vi energy(n);
  repp(i, 1, n) cin >> energy[i];

  vi rats(m);
  vi ratsat(n, -1);
  rep(i, m) {
    cin >> rats[i];
    ratsat[rats[i]] = i;
  }

  dbg(energy, rats);

  // vi done(n);
  // vi entr(n, INF);
  //
  // for (auto i : rats) {
  //   entr[end[i]] = min(entr[end[i]], dists[i]);
  // }
  //
  // dbg(entr);
  //
  // int ans = 0;
  // rep(i, n) {
  //   dbg(i, end[i], t - entr[end[i]] - dist0[end[i]]);
  //   if (done[end[i]]) continue;
  //   ans += max(t - entr[end[i]] - dist0[end[i]], 0LL);
  //   done[end[i]] = 1;
  // }

  vvi dp(n, vi(t, -1));
  function<int(int, int, int)> solve;
  solve = [&](int u, int p, int s) -> int {
    if (dp[u][s] != -1)
      return dp[u][s];

    dbg(u, p, s);
    if (ratsat[u] != -1) {
      dp[u][s] = max(t - dist0[u] - s, 0LL) * energy[u];
      return dp[u][s];
    }

    int ret = INF;
    for (int i = 0; i < t - s; i++) {
      int tmp = i * energy[u];
      for (auto [v, w] : adj[u]) {
        if (v == p)
          continue;
        tmp += solve(v, u, s + i);
      }

      ret = min(ret, tmp);
    }

    dp[u][s] = ret;
    return ret;
  };

  int ans = 0;
  for (auto [u, w] : adj[0]) {
    ans += solve(u, 0, 0);
  }

  cout << ans << endl;
}
