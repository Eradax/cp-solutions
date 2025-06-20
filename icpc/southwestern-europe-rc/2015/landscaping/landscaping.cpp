#include <bits/stdc++.h>

#ifdef DBG
  #define dbg(expr)                                                          \
    cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
         << expr << endl;
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;
#define int ll

template <typename T>
ostream& operator<<(ostream& o, vector<T> v) {
  o << "{";
  for (auto& i : v)
    o << i << ", ";
  o << "}";
  return o;
}

template <typename T, typename G>
ostream& operator<<(ostream& o, pair<T, G> v) {
  o << "{";
  o << v.first << ", " << v.second;
  o << "}";
  return o;
}

#define sz(c) ((int)c.size())

struct Edg {
  int u, v;
  int cap, flo;

  Edg(int u, int v, int cap, int flo) : u(u), v(v), cap(cap), flo(flo) {}
};

ostream& operator<<(ostream& o, Edg v) {
  o << "{";
  o << v.u << ", " << v.v << ", " << v.cap << ", " << v.flo;
  o << "}";
  return o;
}

struct Flow {
  static const int INF = 1e18;

  int n, m;
  int s, t;
  vector<vector<pair<int, int>>> adj;
  vector<Edg> edgs;
  int flow = 0;
  vector<pair<int, int>> par;

  Flow(const vector<vector<pair<int, int>>>& adj2, int ss = 0, int tt = -1) {
    n = sz(adj2);
    m = 0;

    s = ss;
    t = tt;
    if (t == -1)
      t = n - 1;

    adj.resize(n);
    par.resize(n, make_pair(-1, -1));

    for (int u = 0; u < n; u++) {
      for (int i = 0; i < sz(adj2[u]); i++) {
        auto [v, w] = adj2[u][i];
        m++;

        int eid = sz(edgs);
        edgs.emplace_back(u, v, w, 0);
        edgs.emplace_back(v, u, 0, 0);

        dbg(u);
        dbg(v);
        dbg(eid);

        adj[u].emplace_back(v, eid);
        adj[v].emplace_back(u, eid + 1);
      }
    }

    constflow();
  }

  void constflow() {
    while (augment(s, t)) {
    }
  }

  bool augment(int s, int t) {
    if (!bfs(s, t))
      return 0;

    int f = INF;
    for (int cur = t; cur != s; cur = par[cur].first) {
      int eid = par[cur].second;
      f = min(f, edgs[eid].cap - edgs[eid].flo);
    }

    flow += f;

    for (int cur = t; cur != s; cur = par[cur].first) {
      int eid = par[cur].second;
      edgs[eid].flo += f;
      edgs[eid ^ 1].flo -= f;
    }

    return 1;
  }

  bool bfs(int s, int t) {
    par.assign(n, make_pair(-1, -1));
    par[s] = make_pair(-2, -2);

    queue<int> q;
    q.emplace(s);
    while (sz(q)) {
      auto u = q.front();
      q.pop();

      for (auto [v, eid] : adj[u]) {
        if (par[v].first != -1 || edgs[eid].cap - edgs[eid].flo <= 0)
          continue;
        par[v] = make_pair(u, eid);
        if (v == t)
          return 1;

        q.emplace(v);
      }
    }

    return 0;
  }
};

void solve(int n, int m) {
  int a, b;
  cin >> a >> b;

  vector<vector<pair<int, int>>> adj(2 + n * m);
  for (int i = 0; i < n; i++) {
    string str;
    cin >> str;

    for (int j = 0; j < m; j++) {
      int cur = i * m + j;
      if (i) {
        int prev = (i - 1) * m + j;
        adj[cur].emplace_back(prev, a);
        adj[prev].emplace_back(cur, a);
      }

      if (j) {
        int prev = i * m + j - 1;
        adj[cur].emplace_back(prev, a);
        adj[prev].emplace_back(cur, a);
      }

      if (str[j] == '#') {
        adj[n * m].emplace_back(cur, b);
      } else {
        adj[cur].emplace_back(n * m + 1, b);
      }
    }
  }

  Flow flow(adj, n * m, n * m + 1);

  cout << flow.flow << endl;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;
  solve(n, m);
}
