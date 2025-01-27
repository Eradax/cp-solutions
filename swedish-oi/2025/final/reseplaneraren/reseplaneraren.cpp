#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = long long;

#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

static constexpr int INF = 1e18;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define setcontains(c, x) (c.find(x) != c.end())

vvi c;
vvi adj;
vi par;

vector<int> tin, tout;
vector<vector<int>> up;
int timer, l;
int n, k, q;

void dfs(int u, int p) {
  par[u] = p;
  if (p >= 0) c[p].push_back(u);

  tin[u] = ++timer;
  up[u][0] = max(p, 0LL);
  repp(i, 1, l + 1) { up[u][i] = up[up[u][i - 1]][i - 1]; }

  for (auto v : adj[u]) {
    if (v == p)
      continue;

    dfs(v, u);
  }

  tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
  if (is_ancestor(u, v))
    return u;
  if (is_ancestor(v, u))
    return v;
  for (int i = l; i >= 0; --i) {
    if (!is_ancestor(up[u][i], v))
      u = up[u][i];
  }
  return up[u][0];
}

void preprocess(int root) {
  tin.resize(n);
  tout.resize(n);
  timer = 0;
  l = ceil(log2(n));
  up.assign(n, vector<int>(l + 1));
  dfs(root, -1);
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> k >> q;

  adj.resize(n);

  rep(i, n - 1) {
    int u, v;
    cin >> u >> v;
    u--;
    v--;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  dbg(adj);

  c.resize(n);
  par.resize(n, -1);

  preprocess(0);

  dbg(par);
  dbg(c);

  unordered_set<int> seen;

  rep(i, k) {
    int s, t;
    cin >> s >> t;
    s--;
    t--;

    dbg(s, t);

    if (lca(s, t) == 0) {
      while (s >= 0 && !setcontains(seen, s)) {
        seen.insert(s);
        s = par[s];
      }

      while (t >= 0 && !setcontains(seen, t)) {
        seen.insert(t);
        t = par[t];
      }
    }
  }

  dbg(seen);

  rep(i, q) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    if (setcontains(seen, a) || setcontains(seen, b)) {
      cout << "Yes" << '\n';
    } else {
      cout << "No" << '\n';
    }
  }
}
