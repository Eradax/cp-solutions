#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static constexpr int INF = 1e9;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()
#define setcontains(c, x) (c.find(x) != c.end())

struct T {
  vi t;
  int n;
  T(int n) : t(2 * n, 0), n(n) { dbg(n); }

  void inc(int i) {
    i += n;
    t[i]++;
    for (i /= 2; i > 0; i /= 2) {
      t[i] = t[2 * i] + t[2 * i + 1];
    }
  }

  int sum(int l, int r) {
    int ans = 0;
    l += n;
    r += n;
    for (; l < r; l /= 2, r /= 2) {
      if (l % 2)
        ans += t[l++];
      if (r % 2)
        ans += t[--r];
    }

    return ans;
  }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k, q;
  cin >> n >> k >> q;

  vvi adj(n);

  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dbg(adj);

  int l = ceil(log2(n));
  vvi up(n, vi(l + 1));
  vi depth(n);

  vi tin(n), tout(n);

  {  // create euler tour
    int tim = 0;
    function<void(int, int, int)> et;
    et = [&](int u, int p, int dep) {
      tin[u] = ++tim;

      depth[u] = dep;

      up[u][0] = p;

      repp(i, 1, l + 1) {
        up[u][i] = up[up[u][i - 1]][i - 1];
      }

      for (auto v : adj[u]) {
        if (v == p) {
          continue;
        }

        et(v, u, dep + 1);
      }

      tout[u] = ++tim;
    };

    et(0, 0, 0);
  }

  auto is_ancestor = [&](int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  };

  auto lca = [&](int a, int b) {
    if (is_ancestor(a, b))
      return a;

    if (is_ancestor(b, a))
      return b;

    per(i, l + 1) {
      if (!is_ancestor(up[a][i], b))
        a = up[a][i];
    }

    return up[a][0];
  };

  dbg(tin, tout);
  dbg(depth);

  vi uplo(n, INF);
  vpi points;
  rep(i, k) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;

    dbg(s, t);

    uplo[s] = min(uplo[s], depth[lca(s, t)]);
    uplo[t] = min(uplo[t], depth[lca(s, t)]);

    points.emplace_back(tin[s], tin[t]);
    points.emplace_back(tin[t], tin[s]);
  }

  vector<tuple<int, int, int>> t1_queries;
  vector<tuple<int, int, int, int, int>> t2_queries;
  rep(i, q) {
    int a, b, c, d;
    cin >> a >> b;
    a--;
    b--;

    dbg(a, b);

    if (is_ancestor(a, b)) {
      t1_queries.emplace_back(a, b, i);
    } else if (is_ancestor(b, a)) {
      t1_queries.emplace_back(b, a, i);
    } else {
      d = tout[b];
      c = tin[b];
      b = tout[a];
      a = tin[a];

      dbg(a, b, c, d);

      t2_queries.emplace_back(d, a, b, i, 1);
      t2_queries.emplace_back(c - 1, a, b, i, -1);
    }
  }

  dbg(t1_queries, t2_queries);

  vi ans(q);

  {  // begin t1
    vi maxup(n, INF);
    function<int(int, int)> dfs;
    dfs = [&](int u, int p) {
      int ans = INF;

      ans = min(ans, uplo[u]);

      dbg(ans, uplo[u]);

      for (auto v : adj[u]) {
        if (v == p)
          continue;

        ans = min(ans, dfs(v, u));
      }

      return maxup[u] = ans;
    };

    dfs(0, -1);

    dbg(maxup);

    for (auto [a, b, i] : t1_queries) {
      dbg(a, b, i);
      dbg(depth[a], maxup[b]);

      if (maxup[b] <= depth[a]) {
        ans[i] = 1;
      } else {
        ans[i] = 0;
      }
    }

  }  // end t1

  dbg(ans);

  {  // begin t2
    sort(all(t2_queries));
    sort(all(points), [](pi a, pi b) { return a.second < b.second; });

    dbg(points);

    int pp = 0;
    T t(2 * n + 5);

    for (auto [a, b, c, d, e] : t2_queries) {
      while (pp < sz(points) && points[pp].second <= a) {
        t.inc(points[pp].first);
        pp++;
      }

      dbg(b, c);
      ans[d] += e * t.sum(b, c + 1);
    }
  }  // end t2

  dbg(ans);

  rep(i, q) {
    cout << (ans[i] > 0 ? "Yes" : "No") << endl;
  }
}
