#include <bits/stdc++.h>

#ifdef DBG
  #define dbg(expr)                                                          \
    cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
         << expr << endl
#else
  #define dbg(...)
#endif

using namespace std;

template <typename T, typename G>
ostream& operator<<(ostream& o, const pair<T, G>& p) {
  o << "{" << p.first << ", " << p.second << "}";
  return o;
}

template <typename T>
ostream& operator<<(ostream& o, const vector<T>& p) {
  o << "{";
  for (auto& i : p)
    o << i << ", ";
  o << "}";
  return o;
}

#define sz(c) ((int)c.size())

const int INF = 1e9;

struct Edg {
  int u, v;
  int c;

  Edg(int u, int v) : u(u), v(v), c(1) {}
  Edg(int u, int v, int c) : u(u), v(v), c(c) {}
};

ostream& operator<<(ostream& o, const Edg& e) {
  o << "{" << e.u << ", " << e.v << ", " << e.c << "}";
  return o;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  dbg(n);
  dbg(m);

  vector<Edg> edgs;
  vector<vector<pair<int, int>>> adj(n);

  for (int i = 0; i < m; i++) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;
    edgs.emplace_back(u, v, 1);
    edgs.emplace_back(v, u, 0);
    adj[u].emplace_back(v, 2 * i);
    adj[v].emplace_back(u, 2 * i + 1);
  }

  dbg(edgs);

  // max flow
  auto bfs = [&](vector<pair<int, int>>& pa) {
    pa.assign(n, make_pair(-1, -1));
    pa[0].first = -2;
    pa[0].second = -2;

    dbg(pa);

    queue<pair<int, int>> q;
    q.emplace(0, INF);
    while (sz(q)) {
      auto [u, w] = q.front();
      q.pop();

      for (auto [v, eid] : adj[u]) {
        if (pa[v].first == -1 && edgs[eid].c) {
          pa[v].first = u;
          pa[v].second = eid;
          int nf = min(w, edgs[eid].c);
          if (v == n - 1)
            return nf;
          q.emplace(v, nf);
        }
      }
    }

    return 0;
  };

  int f = 0;
  int nf;
  vector<pair<int, int>> pa(n);
  while ((nf = bfs(pa))) {
    dbg(pa);
    dbg(f);
    dbg(nf);
    f += nf;
    int cur = n - 1;
    while (cur) {
      dbg(cur);
      auto [pr, eid] = pa[cur];
      edgs[eid].c -= nf;
      edgs[eid ^ 1].c += nf;
      cur = pr;
    }
  }

  vector<vector<int>> paths;
  function<int(int)> dfs = [&](int u) -> int {
    dbg(u);
    dbg(paths.back());
    paths.back().push_back(u);
    if (u == n - 1)
      return 1;

    for (auto [v, eid] : adj[u]) {
      if (eid % 2)
        continue;
      if (edgs[eid ^ 1].c) {
        edgs[eid ^ 1].c--;
        if (!dfs(v))
          edgs[eid ^ 1].c++;
        else
          return 1;
      }
    }

    paths.back().pop_back();
    return 0;
  };

  for (int i = 0; i < f; i++) {
    paths.push_back(vector<int>());
    dfs(0);
  }

  cout << f << endl;
  for (int i = 0; i < f; i++) {
    cout << sz(paths[i]) << '\n';
    for (auto i : paths[i])
      cout << i+1 << " ";
    cout << '\n';
  }
}
