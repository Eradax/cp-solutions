#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define perr(i, s, n) for (int i = n - 1; i >= s; i--)
#define per(i, n) perr(i, 0, n)

#define all(c) c.begin(), c.end()

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static const int INF = 1e9;

struct Cd {
  int n;
  vi sz, pa, ans;
  // vector<unordered_map<int, int>> dist;
  // vector<set<int>> madj;
  vvi dist;
  vvi madj;

  Cd(int n, const vvi& adj)
      : n(n), madj(adj), sz(n), pa(n), ans(n, INF), dist(n) {
    // rep(i, n) madj[i].insert(all(adj[i]));

    // rep(i, n) dist[i].push_back(0);

    dbg(madj);

    build(0, -1);

    rep(i, n) reverse(all(dist[i]));

    dbg(sz, pa, ans);
  }

  int centroid(int u, int p, int n) {
    for (auto v : madj[u]) {
      if (v == p)
        continue;
      if (sz[v] <= n / 2)
        continue;
      return centroid(v, u, n);
    }
    return u;
  };

  int dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : madj[u]) {
      if (v == p)
        continue;
      sz[u] += dfs(v, u);
    }
    return sz[u];
  };

  void dfs2(int u, int p, int d) {
    dist[u].push_back(d);
    for (auto v : madj[u]) {
      if (v == p)
        continue;
      dfs2(v, u, d + 1);
    }
  };

  void build(int u, int p) {
    int n = dfs(u, p);
    int c = centroid(u, p, n);
    pa[c] = p;

    dfs2(c, p, 0);

    vi tmp(all(madj[c]));
    for (auto v : tmp) {
      madj[c].erase(find(all(madj[c]), v));
      madj[v].erase(find(all(madj[v]), c));
      build(v, c);
    }
  };

  void upd(int u) {
    int i = 0;
    for (int v = u; v != -1; v = pa[v], i++)
      ans[v] = min(ans[v], dist[u][i]);
  };

  int query(int u) {
    int ret = INF;
    int i = 0;
    for (int v = u; v != -1; v = pa[v], i++) {
      ret = min(ret, dist[u][i] + ans[v]);

      // dbg(ret, prev, v, u);
    }
    return ret;
  };
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vvi adj(n);
  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  dbg(adj);

  Cd cd(n, adj);
  cd.upd(0);

  rep(i, q) {
    int t, u;
    cin >> t >> u;

    dbg(t, u);

    if (t == 0) {
      cd.upd(u);
    } else {
      cout << cd.query(u) << '\n';
    }
  }
}
