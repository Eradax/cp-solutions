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

  vvpi adj(n);
  vpi par(n);
  vi dist0(n);

  int l = ceil(log2(n)) + 1;
  vvi up(n, vi(l + 1));
  vvpi upmin(n, vpi(l + 1, {INF, -1}));

  vi tin(n), tout(n);

  rep(_, n - 1) {
    int a, b, ti;
    cin >> a >> b >> ti;
    adj[a].emplace_back(b, ti);
    adj[b].emplace_back(a, ti);
  }

  vi energy(n, INF);
  repp(i, 1, n) cin >> energy[i];

  vi rats;
  vector<bool> ratsat(n);
  rep(i, m) {
    int tmp;
    cin >> tmp;
    ratsat[tmp] = 1;
  }

  {
    int tim = 0;
    function<void(int, int, int)> dfs;
    dfs = [&](int u, int p, int w) {
      tin[u] = ++tim;
      up[u][0] = p;
      upmin[u][0] = {energy[p], p};

      par[u] = {p, w};

      repp(i, 1, l + 1) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        upmin[u][i] = min(upmin[u][i - 1], upmin[up[u][i - 1]][i - 1]);
      }

      if (ratsat[u] == 0) {
        for (auto [v, w] : adj[u]) {
          if (v == p)
            continue;
          dist0[v] = w + dist0[u];

          if (dist0[v] >= t) continue;
          dfs(v, u, w);
        }
      } else {
        rats.push_back(u);
      }

      tout[u] = ++tim;
    };
    dfs(0, 0, 0);
    par[0] = {-1, 0};
  }

  dbg(up, upmin);

  auto is_ancestor = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  };

  auto lca = [&](int u, int v) {
    // dbg(u, v);
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;

    per(i, l + 1) {
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    }
    u = up[u][0];

    // dbg(u);

    return u;
  };

  auto rmq = [&](int u, int v) {
    pi ans = {INF, INF};

    dbg(u, v);

    per(i, l + 1) {
      if (!is_ancestor(up[u][i], v)) {
        ans = min(ans, upmin[u][i]);
        u = up[u][i];
      }
    }

    ans = min(ans, upmin[u][0]);
    u = up[u][0];

    dbg(u, v);
    assert(u == v);

    return ans;
  };

  // auto solve_one = [&](int node) -> pi {
  //   int ans = INF;
  //
  //   int bs;
  //
  //   int d = max(t - dist0[node], 0LL);
  //   while (node != 0) {
  //     dbg(node, d, energy[node - 1]);
  //     if (energy[node] * d < ans) {
  //       ans = energy[node] * d;
  //       bs = node;
  //     }
  //     node = par[node];
  //   }
  //
  //   return {ans, bs};
  // };

  dbg(rats);

  sort(all(rats), [&](int a, int b) { return dist0[a] < dist0[b]; });

  dbg(rats);

  vi done(sz(rats));

  auto getnxt = [&](int u, bool include_u = true, int start = 0) {
    start = 0;
    // dbg(u, include_u, start);
    if (!ratsat[u] || !include_u) {
      vi tmp;
      repp(i, start, sz(rats)) {
        if (!is_ancestor(u, rats[i]) && !done[i])
          tmp.push_back(rats[i]);
      }
      sort(all(tmp), [&](int a, int b) {
        return dist0[lca(a, u)] > dist0[lca(b, u)];
      });

      // dbg(u, tmp);
      u = tmp.empty() ? 0 : tmp[0];
      // dbg(u);
    }

    return u;
  };

  // int cnt = 0;

  vi dp(n, -1);
  function<int(int, int, int)> solve;
  solve = [&](int u, int time, int maxdone) -> int {
    // if (++cnt >= 10)
    //   exit(1);
    // dbg(u, time, maxdone);

    u = getnxt(u, 1, maxdone);
    // dbg(u);

    if (dp[u] != -1)
      return dp[u];

    if (u == 0) {
      dp[u] = 0;
      return 0;
    }

    done[find(all(rats), u) - rats.begin()]++;

    dbg(u, time, maxdone);

    int ret = INF;

    {
      int nu = getnxt(u, 0, maxdone + 1);

      dbg(nu);

      if (lca(nu, u) != 0) {
        int cost = max(dist0[nu] - dist0[u], 0LL) *
                   min(energy[u], rmq(u, lca(nu, u)).first);

        dbg(cost);

        ret = min(
            ret,
            cost + solve(
                       nu,
                       0,
                       max(maxdone,
                           (int)distance(rats.begin(), find(all(rats), nu)))
                   )
        );
      }

      dbg("**************", ret, u, nu);
    }

    if (u != 0) {
      pi minn = min(upmin[u][l], {energy[u], u});
      dbg(minn.first * max(t - dist0[u], 0LL));
      dbg(minn);

      int nu = getnxt(minn.second, 0, maxdone + 1);
      int nmaxdone = maxdone;
      if (find(all(rats), nu) != rats.end()) {
        nmaxdone = max(
            nmaxdone, (int)distance(rats.begin(), find(all(rats), nu))
        );
      }
      dbg(nu);

      ret = min(
          ret,
          minn.first * max(t - dist0[u], 0LL) +
              solve(
                  nu, time + dist0[u] - dist0[par[minn.second].first], nmaxdone
              )
      );
      dbg("!!!!!!!!!!!!!!!", ret, u);
    }

    // solve for next shallowest in subtree
    // ret = min(ret, solve(next shallowest subtree)

    // dbg("**************", ret, u, nu);

    done[find(all(rats), u) - rats.begin()]--;
    dp[u] = ret;
    return ret;
  };

  for (auto i : rats)
    solve(i, 0, find(all(rats), i) - rats.begin());

  dbg(dp);

  dbg(dp[0]);

  cout << (rats.empty() ? 0 : dp[rats[0]]) << endl;
}
