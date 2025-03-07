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

using ll = long long;
#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static constexpr int INF = 1e9;
struct Train {
  int u, v, t, d;
  Train(int u, int v, int t, int d) : u(u), v(v), t(t), d(d) {}

  auto operator<(const Train& o) { return t < o.t; }
};

ostream& operator<<(ostream& os, const Train& t) {
  os << t.u << ' ' << t.v << ' ' << t.t << ' ' << t.d;
  return os;
}

signed main() {
  int n, k;
  cin >> n >> k;

  int ssum = 0;
  int mint = INF;

  vvpi adj(n);

  rep(_, n - 1) {
    int u, v, s;
    cin >> u >> v >> s;
    --u;
    --v;

    ssum += s;

    adj[u].emplace_back(v, s);
    adj[v].emplace_back(u, s);
  }

  for (auto adjrow : adj)
    dbg(adjrow);

  int l = ceil(log2(n)) + 1;
  vvi up(n, vi(l + 1));
  vvi uptime(n, vi(l + 1));

  vi tin(n), tout(n);

  {
    int time = 0;
    function<void(int, int, int)> dfs;
    dfs = [&](int u, int p, int w) {
      tin[u] = ++time;

      up[u][0] = p;
      uptime[u][0] = w;

      repp(i, 1, l + 1) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        uptime[u][i] = uptime[u][i - 1] + uptime[up[u][i - 1]][i - 1];
      }

      for (auto [v, ww] : adj[u]) {
        if (v == p)
          continue;
        dfs(v, u, ww);
      }

      tout[u] = ++time;
    };
    dfs(0, 0, 0);
  }

  dbg(up, uptime);

  auto is_ancestor = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  };

  auto lca = [&](int u, int v) {
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;

    per(i, l + 1) {
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    }

    return up[u][0];
  };

  auto dist = [&](int u, int v) {
    dbg(u, v);

    int lc = lca(u, v);

    int ans = 0;
    per(i, l + 1) {
      if (!is_ancestor(up[u][i], v)) {
        ans += uptime[u][i];
        u = up[u][i];
      }
    }

    if (!is_ancestor(u, v)) {
      ans += uptime[u][0];
      u = up[u][0];
    }

    per(i, l + 1) {
      if (!is_ancestor(up[v][i], u)) {
        ans += uptime[v][i];
        v = up[v][i];
      }
    }

    if (!is_ancestor(v, u)) {
      ans += uptime[v][0];
      v = up[v][0];
    }

    // dbg(u, v, lc);

    assert(v == u && v == lc);

    return ans;
  };

  rep(i, n) {
    rep(j, n) {
      dbg(dist(i, j));
    }
  }

  vvi dag(k);
  vector<Train> trains;

  rep(i, k) {
    int u, v, t, d;
    cin >> u >> v >> t >> d;
    u--, v--;

    mint = min(mint, t);

    trains.emplace_back(u, v, t, d);
  }

  dbg(trains);

  sort(all(trains));

  dbg(trains);

  rep(i, k) {
    auto [u, v, t, d] = trains[i];
    repp(j, i + 1, k) {
      auto [nu, nv, nt, nd] = trains[j];

      if (t + d + dist(v, nu) > nt)
        continue;

      // dag[i].emplace_back(j, d + dist(v, nu));
      dag[i].push_back(j);
    }
  }

  for (auto dagrow : dag)
    dbg(dagrow);

  vi dp(k, -1);
  function<int(int)> dfs;
  dfs = [&](int u) {
    if (dp[u] != -1)
      return dp[u];

    int ans = 1;
    for (auto v : dag[u])
      ans = max(ans, 1 + dfs(v));

    return dp[u] = ans;
  };

  rep(i, k) dfs(i);

  vi ans(n);
  if (mint > ssum) {
    int best = 0;
    rep(j, k) {
      best = max(best, dp[j]);
    }

    rep(i, n) ans[i] = best;
  } else {
    rep(i, n) {
      int best = 0;
      rep(j, k) {
        if (dist(i, trains[j].u) <= trains[j].t)
          best = max(best, dp[j]);
      }

      ans[i] = best;
    }
  }

  rep(i, n) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
