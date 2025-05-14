#include <bits/stdc++.h>

#ifdef DBG
  #define dbg(expr)                                                          \
    cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
         << expr << endl;
#else
  #define dbg(...)
#endif

using namespace std;

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
  static const int INF = 1e9;

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
      int eid = par[cur].second;  // NOTE: Maybe this should be flipped?
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
  vector<int> p(n);
  for (auto& i : p)
    cin >> i;
  int pold = p.back();

  dbg(p);

  int goalflow = 0;

  vector<vector<pair<int, int>>> adj(2 + m + n);
  for (int i = 0; i < m; i++) {
    int a, b;
    cin >> a >> b;
    a--, b--;

    if (a == n - 1) {
      p[n - 1] += 2;

      adj[0].emplace_back(1 + i, 2);
      adj[1 + i].emplace_back(1 + m + a, 2);
      adj[1 + i].emplace_back(1 + m + b, 0);
      continue;
    }

    if (b == n - 1) {
      p[n - 1] += 2;

      adj[0].emplace_back(1 + i, 2);
      adj[1 + i].emplace_back(1 + m + a, 0);
      adj[1 + i].emplace_back(1 + m + b, 2);
      continue;
    }

    adj[0].emplace_back(1 + i, 2);
    adj[1 + i].emplace_back(1 + m + a, 2);
    adj[1 + i].emplace_back(1 + m + b, 2);
  }

  dbg(p);

  for (int i = 0; i < n - 1; i++) {
    if (p[n - 1] - p[i] - 1 < 0) {
      cout << "NO" << '\n';
      return;
    }
    adj[1 + m + i].emplace_back(1 + n + m, p[n - 1] - p[i] - 1);
    goalflow += p[n - 1] - p[i] - 1;
    dbg(i);
    dbg(1 + n + i);
    dbg(p[n - 1] - p[i] - 1);
  }

  adj[1 + m + n - 1].emplace_back(1 + n + m, p[n - 1] - pold);
  goalflow += p[n - 1] - pold;

  goalflow = min(goalflow, 2 * m);

  Flow flow(adj);

  dbg(flow.flow);
  dbg(goalflow);
  dbg(flow.edgs);

  // if (flow.flow != goalflow) {
  //   cout << "NO" << '\n';
  //   return;
  // }

  vector<int> ans(m);
  for (int i = 0; i < m; i++) {
    int eid = 2 * (m + 2 * i);
    dbg(eid);
    ans[i] = 2 - flow.edgs[eid].flo;

    int su = flow.edgs[eid].flo + flow.edgs[eid + 2].flo;
    if (su != 2) {
      cout << "NO" << '\n';
      return;
    }
  }

  for (auto i : ans)
    cout << i << " ";
  cout << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  while (cin >> n >> m)
    solve(n, m);
}
