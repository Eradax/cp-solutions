#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define sz(c) ((int)c.size())

struct Pipe {
  int u, v, a, b;

  Pipe(int u, int v, int a, int b) : u(u), v(v), a(a), b(b) {}

  friend std::ostream& operator<<(std::ostream& os, const Pipe& pipe) {
    os << "Pipe(" << pipe.u << ", " << pipe.v << ", " << pipe.a << ", "
       << pipe.b << ")";
    return os;
  }
};

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, q;
  cin >> n >> m >> q;

  vector<Pipe> pipes;
  vvpi adj(n);
  vvpi adj2(n);

  rep(i, m) {
    int u, v, a, b;
    cin >> u >> v >> a >> b;
    u--, v--, a--, b--;

    adj[u].emplace_back(v, sz(pipes));
    adj[v].emplace_back(u, sz(pipes));

    adj2[u].emplace_back(v, a);
    adj2[v].emplace_back(u, b);

    pipes.emplace_back(u, v, a, b);
  }

  int num_bcc = 0;
  vi bcc_id(m, -1);

  {
    vi num(n), low(n);
    int time = 0;
    stack<int> st;

    function<void(int, int)> dfs;
    dfs = [&](int u, int e) {
      num[u] = low[u] = ++time;
      int c = 0;

      for (auto [v, ve] : adj[u]) {
        if (ve == e)
          continue;
        if (num[v] == 0) {
          c++;
          st.push(ve);
          dfs(v, ve);

          low[u] = min(low[u], low[v]);

          if ((e == -1 && c > 1) || (e != -1 && low[v] >= num[u])) {
            while (!st.empty()) {
              int edge = st.top();
              st.pop();

              bcc_id[edge] = num_bcc;
              if (edge == ve)
                break;
            }
            num_bcc++;
          }
        } else if (num[v] < num[u]) {
          st.push(ve);
          low[u] = min(low[u], num[v]);
        }
      }
    };

    for (int u = 0; u < n; u++) {
      if (num[u] == 0) {
        dfs(u, -1);
        if (sz(st)) {
          while (!st.empty()) {
            int edge = st.top();
            st.pop();

            bcc_id[edge] = num_bcc;
          }
          num_bcc++;
        }
      }
    }
  }

  dbg(pipes);
  dbg(bcc_id);

  unordered_map<ll, int> trans;
  auto hashp = [&](int a, int b) -> ll { return (ll)a * ll(1e6) + b; };
  auto get_ind = [&](int a, int b) {
    ll x = hashp(a, b);
    if (trans.find(x) != trans.end()) {
      return trans[x];
    }
    dbg(a, b, sz(trans));
    return trans[x] = sz(trans);
  };

  vvi ratg(6 * m);

  auto add_edge = [&](int a, int b, int c, int d) {
    int u = get_ind(a, b);
    int v = get_ind(c, d);
    dbg(u, v);
    ratg[u].push_back(v);
  };

  {
    int l = n;
    for (int u = 0; u < n; u++) {
      for (auto [v, _] : adj[u])
        add_edge(v, u, l, u);
      l++;
    }

    for (int u = 0; u < n; u++) {
      for (auto [v, e] : adj2[u])
        add_edge(u, v, v, e);
    }

    for (int u = 0; u < n; u++) {
      unordered_map<int, vi> g;
      for (auto [v, e] : adj[u])
        g[bcc_id[e]].push_back(v);

      for (auto gg : g) {
        for (auto x : gg.second) {
          add_edge(x, u, l, u);
          add_edge(l, u, x, u);
        }
        l++;
      }
    }
  }

  for (auto i : ratg)
    dbg(i);
  dbg(ratg);

  vi vis(sz(ratg));

  {
    int s, r, t, ss = -1;
    cin >> s >> r >> t;
    s--, r--; t--;

    {
      vi vis(n);
      queue<int> q;

      q.push(s);
      vis[s] = 1;

      bool flag = 0;

      while (sz(q)) {
        if (flag)
          break;

        int u = q.front();
        q.pop();

        for (auto [v, _] : adj[u]) {
          if (v == r) {
            ss = u;
            flag = 1;
            break;
          }
          if (vis[v])
            continue;

          vis[v] = 1;
          q.push(v);
        }
      }
    }

    assert(ss >= 0);

    s = ss;

    dbg(s, r, t);

    {
      queue<int> q;

      int start = get_ind(s, r);
      dbg(s, r, start);
      q.push(start);
      vis[start] = 1;

      while (sz(q)) {
        int u = q.front();
        q.pop();

        for (auto v : ratg[u]) {
          if (vis[v])
            continue;

          vis[v] = 1;
          q.push(v);
        }
      }
    }

    int node = get_ind(t + n, t);

    for (auto i : vis)
      dbg(i);
    dbg(vis);

    cout << vis[node] << '\n';
  }

  for (int i = 1; i < q; i++) {
    int s, r, t, ss = -1;
    cin >> s >> r >> t;
    s--, r--, t--;

    dbg(s, r, t);

    int node = get_ind(t + n, t);

    for (auto i : vis)
      dbg(i);
    dbg(vis);

    cout << vis[node] << '\n';
  }
}
