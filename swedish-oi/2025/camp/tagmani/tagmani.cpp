#pragma GCC optimize("Ofast")
#include <bitset>
#pragma GCC target("avx2")
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

struct Cd {
  int n;
  vi sz, pa;
  // vector<unordered_map<int, int>> dist;
  // vector<set<int>> madj;
  vvi dist;
  vector<map<int, int>> best;
  vvpi adj;

  Cd(int n, const vvpi& adj) : n(n), adj(adj), sz(n), pa(n), dist(n), best(n) {
    dbg(adj);

    build({0, -1}, -1);

    rep(i, n) reverse(all(dist[i]));

    dbg(sz, pa, dist);
  }

  pi centroid(pi u, int p, int n) {
    for (auto v : adj[u.first]) {
      if (v.first == p)
        continue;
      if (sz[v.first] <= n / 2)
        continue;
      return centroid(v, u.first, n);
    }
    return u;
  };

  int dfs(int u, int p) {
    sz[u] = 1;
    for (auto v : adj[u]) {
      if (v.first == p)
        continue;
      sz[u] += dfs(v.first, u);
    }
    return sz[u];
  };

  void dfs2(int u, int p, int d) {
    dist[u].push_back(d);
    for (auto v : adj[u]) {
      if (v.first == p)
        continue;
      dfs2(v.first, u, d + v.second);
    }
  };

  void build(pi u, int p) {
    int n = dfs(u.first, p);
    pi c = centroid(u, p, n);
    pa[c.first] = p;

    dfs2(c.first, p, 0);

    vpi tmp(all(adj[c.first]));
    for (auto v : tmp) {
      rep(i, (adj[c.first].size())) {
        if (adj[c.first][i].first != v.first)
          continue;
        adj[c.first].erase(adj[c.first].begin() + i);
        break;
      }
      // adj[c.first].erase(find(all(adj[c.first]), v));
      // adj[v.first].erase(find(all(adj[v.first]), c));
      rep(i, (adj[v.first].size())) {
        if (adj[v.first][i].first != c.first)
          continue;
        adj[v.first].erase(adj[v.first].begin() + i);
        break;
      }
      build(v, c.first);
    }
  };

  void upd(int u, int d, int p) {
    for (int v = u, i = 0; v != -1; v = pa[v], i++) {
      int nd = d - dist[u][i];

      dbg(u, v, d, p);

      auto it = best[v].lower_bound(nd);

      if (it != best[v].end() && (*it).second >= p) {
        continue;
      }

      // map<int, int> tmp(all(best[v]));

      dbg(best[v]);

      auto itt = best[v].lower_bound(nd);

      while (itt != best[v].begin()) {
        if (best[v].begin() == best[v].end())
          break;
        
        itt--;

        // dbg("t");
        // dbg(distance(best[v].begin(), itt));
        // dbg("x");

        dbg(itt == best[v].begin());
        dbg(itt == best[v].end());
        dbg(distance(best[v].begin(), itt));

        dbg(*itt);

        if ((*itt).second <= p) {
          itt = best[v].erase(itt);
        } else {
          break;
        }
      }

      best[v][nd] = p;
      dbg(best[v]);
    }
  };

  int query(int u, int t) {
    dbg(u, t);
    int ret = 0;
    int i = 0;
    for (int v = u; v != -1; v = pa[v], i++) {
      dbg(u, v, dist[u][i]);
      dbg(best[v]);

      auto it = best[v].lower_bound(t + dist[u][i]);
      int maxp = it != best[v].end() ? (*it).second : 0;

      ret = max(ret, maxp);
    }
    return ret;
  };
};

signed main() {
  int n, k;
  cin >> n >> k;

  vvpi adj(n);

  rep(_, n - 1) {
    int u, v, s;
    cin >> u >> v >> s;
    u--, v--;

    adj[u].emplace_back(v, s);
    adj[v].emplace_back(u, s);
  }

  for (auto adjrow : adj)
    dbg(adjrow);

  Cd cd(n, adj);

  vector<Train> trains;

  rep(i, k) {
    int u, v, t, d;
    cin >> u >> v >> t >> d;
    u--, v--;

    trains.emplace_back(u, v, t, d);
  }

  sort(all(trains));
  dbg(trains);

  reverse(all(trains));

  for (auto [u, v, t, d] : trains) {
    dbg(u, v, t, d);
    int p = cd.query(v, t + d);
    dbg(p);
    cd.upd(u, t, p + 1);
  }

  vi ans(n);
  rep(i, n) {
    ans[i] = cd.query(i, 0);
  }

  rep(i, n) {
    cout << ans[i] << ' ';
  }
  cout << '\n';
}
