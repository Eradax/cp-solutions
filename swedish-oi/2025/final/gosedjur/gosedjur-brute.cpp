#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;

using pi = pair<int, int>;

using vpi = vector<pi>;
using vvpi = vector<vpi>;

using vi = vector<int>;
using vvi = vector<vi>;

using vui = vector<unordered_set<int>>;

using vb = vector<bool>;

using bs = bitset<(int)50000>;

static constexpr int INF = 1e9;

vpi dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define setcontains(c, x) (c.find(x) != c.end())

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, r, c;
  cin >> n >> r >> c;

  vvi grid(r, vi(c, -1));
  vi ans(n, -1);

  rep(i, r) {
    rep(j, c) {
      cin >> grid[i][j];
      grid[i][j]--;
    }
  }

  vui adj(n);
  vi lm(n), rm(n);
  vi lp(n), rp(n);

  repp(rr, 1, r) {
    rep(cc, c) {
      int g = grid[rr][cc];
      int ng = grid[rr - 1][cc];
      if (g != ng)
        adj[g].insert(ng);
    }
  }

  dbg(adj);

  vi cyc(n), col(n);

  function<bool(int)> dfs;
  dfs = [&](int u) {
    dbg(u);

    if (col[u] == 1) {
      return cyc[u] = 1;
    }

    if (col[u] == 2) {
      return cyc[u];
    }

    col[u] = 1;

    bool f = 0;
    for (auto v : adj[u]) {
      f |= dfs(v);
    }

    col[u] = 2;

    // if (!f)
    //   topo.push_back(u);

    return cyc[u] = f;
  };

  vector<bs> cnt(n);
  vb vis(n);

  function<void(int)> dfs2;
  dfs2 = [&](int u) {
    dbg(u);

    if (vis[u]) {
      return;
    }

    vis[u] = 1;

    bs* ans = &cnt[u];

    for (auto v : adj[u]) {
      ans->set(v);
      dfs2(v);
      *ans |= cnt[v];
    }

    return;
  };

  rep(i, n) {
    dbg(cyc);
    dfs(i);
  }

  dbg(cyc);

  rep(i, n) {
    if (!cyc[i]) {
      dbg(i);
      dfs2(i);
      ans[i] = cnt[i].count();
    }
  }

  rep(i, n) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
