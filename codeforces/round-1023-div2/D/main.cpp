// #pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

struct E {
  int d, u, v;

  E(int d, int u, int v) : d(d), u(u), v(v) {}

  bool operator<(const E& o) {
    if (d != o.d)
      return d < o.d;
    if (u != o.u)
      return u < o.u;
    return v < o.v;
  }
};

ostream& operator<<(ostream& o, const E& e) {
  o << "{" << e.d << ", " << e.u << ", " << e.v << "}";
  return o;
}

void solve() {
  int n;
  cin >> n;

  dbg(n);

  vector<vi> adj(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dbg(adj);

  vi rem(n, 0);
  vi dist(n, -1);
  vi par(n, -1);
  vi vis(n, -1);
  int tim = 0;

  auto bfs = [&](int s) {
    tim++;
    dist[s] = 0;
    vis[s] = tim;
    queue<int> q;
    q.push(s);

    while (sz(q)) {
      int u = q.front();
      q.pop();

      for (int v : adj[u]) {
        if (rem[v])
          continue;
        if (dist[v] != -1)
          continue;
        vis[v] = tim;
        dist[v] = dist[u] + 1;
        par[v] = u;
        q.push(v);
      }
    }

    int b = s;
    for (int i = 0; i < n; i++) {
      // if (!rem[i] && (dist[i] > dist[b] || (dist[i] == dist[b] && i > b)))
      if (vis[i] == tim && (dist[i] > dist[b] || (dist[i] == dist[b] && i > b)))
        b = i;
    }

    dbg(s, b);

    return b;
  };

  vector<E> ans;
  int nod = n;
  int cnt = 0;
  while (nod > 0) {
    cnt++;
    dbg(nod);
    dbg(ans);
    dbg(rem);

    dist.assign(n, -1);
    // par.assign(n, -1);

    vi ups;

    for (int i = 0; i < n; i++) {
      if (rem[i])
        continue;
      if (dist[i] != -1)
        continue;
      dbg(i, dist);
      ups.push_back(bfs(i));
    }

    dbg(dist);

    dist.assign(n, -1);
    par.assign(n, -1);

    vi vps;
    for (int u : ups)
      vps.push_back(bfs(u));

    dbg(ups, vps);

    for (int i = 0; i < sz(ups); i++) {
      int u = ups[i];
      int v = vps[i];

      int d = 0;

     dbg(u, v);
      for (int j = v; j != -1; j = par[j]) {
        dbg(j);
        rem[j] = 1;
        nod--;
        d++;
      }

      ans.emplace_back(d, 1 + max(u, v), 1 + min(u, v));
    }
  }

  sort(ans.rbegin(), ans.rend());

  for (auto [d, u, v] : ans) {
    cout << d << ' ' << u << ' ' << v << ' ';
  }
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    solve();
  }
}
