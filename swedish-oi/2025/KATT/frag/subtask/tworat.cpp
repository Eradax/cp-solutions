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

  assert(m <= 2);

  vvpi adj(n);
  vi par(n);
  vi dist0(n);

  int l = ceil(log2(n)) + 1;
  vvi up(n, vi(l + 1));

  vi tin(n), tout(n);

  rep(_, n - 1) {
    int a, b, ti;
    cin >> a >> b >> ti;
    adj[a].emplace_back(b, ti);
    adj[b].emplace_back(a, ti);
  }

  {
    int tim = 0;
    function<void(int, int)> dfs;
    dfs = [&](int u, int p) {
      tin[u] = ++tim;
      up[u][0] = p;

      par[u] = p;

      repp(i, 1, l + 1) {
        up[u][i] = up[up[u][i - 1]][i - 1];
      }

      for (auto [v, w] : adj[u]) {
        if (v == p)
          continue;
        dist0[v] = w + dist0[u];
        dfs(v, u);
      }

      tout[u] = ++tim;
    };
    dfs(0, 0);
    par[0] = -1;
  }

  auto is_ancestor = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  };

  auto lca = [&](int u, int v) {
    dbg(u, v);
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;

    per(i, l + 1) {
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    }
    u = up[u][0];

    dbg(u);

    return u;
  };

  dbg(dist0);
  dbg(adj, par);

  vi energy(n);
  repp(i, 1, n) cin >> energy[i];

  vi rats(m);
  rep(i, m) {
    cin >> rats[i];
  }

  auto solve_one = [&](int node) -> pi {
    int ans = INF;

    int bs;

    int d = max(t - dist0[node], 0LL);
    while (node != 0) {
      dbg(node, d, energy[node - 1]);
      if (energy[node] * d < ans) {
        ans = energy[node] * d;
        bs = node;
      }
      node = par[node];
    }

    return {ans, bs};
  };

  if (m == 1) {
    cout << solve_one(rats[0]).first << endl;
    return 0;
  }

  int r1 = rats[0];
  int r2 = rats[1];

  dbg(r1, r2);

  int lc = lca(r1, r2);

  dbg(lc);

  int ans = 0;

  if (lc == r1 || lc == r2) {
    ans = solve_one(lc).first;
    dbg("eq", ans);
  } else if (lc == 0) {
    ans = solve_one(r1).first + solve_one(r2).first;
    dbg("uq", ans);
  } else {
    // options: solve both on their own bits, the one before places further up
    // the one before pauses and the joins the other one

    if (dist0[r1] > dist0[r2])
      swap(r1, r2);

    pi s1 = solve_one(r1);
    pi s2 = solve_one(r2);

    pi s3 = solve_one(lc);

    ans = INF;
    ans = min(ans, s1.first + s2.first);
    ans = min(ans, energy[s3.second] * max(t - dist0[r2], 0LL) + energy[s1.second] * (dist0[r2] - dist0[r1]));
    ans = min(ans, energy[s3.second] * max(t - dist0[r1], 0LL));

    dbg("sh", ans);
  }

  dbg(energy, rats);

  cout << ans << endl;
}
