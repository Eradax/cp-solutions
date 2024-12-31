#include <bits/stdc++.h>

#ifdef DBG
#include "../../../dbg.h"
#else
#define dbg(...)
#endif

/*
links:
    https://open.kattis.com/problems/liftkarta
source:
    Doris 2024 deltävling 2
*/

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)
#define per(i, n) for (int i = n; i >= 0; i--)
#define sz(c) ((int)c.size())

struct UF {
  vector<int> e;
  UF(int n) : e(n, -1) {}
  bool sameSet(int a, int b) { return find(a) == find(b); }
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return false;

    if (e[a] > e[b])
      swap(a, b);

    e[a] += e[b];
    e[b] = a;
    return true;
  }
};

vector<vector<pair<int, int>>> adj, adj_tree;

vector<vector<int>> up, upmax;
vector<int> tin, tout;
int timer = 0;
int l;

void dfs(int u, int p, int ew) {
  up[u][0] = p;
  upmax[u][0] = ew;
  tin[u] = ++timer;

  for (int i = 1; i <= l; i++) {
    up[u][i] = up[up[u][i - 1]][i - 1];
    upmax[u][i] = max(upmax[u][i - 1], upmax[up[u][i - 1]][i - 1]);
  }

  for (auto v : adj_tree[u]) {
    if (v.first == p)
      continue;

    dfs(v.first, u, v.second);
  }

  tout[u] = ++timer;
}

bool is_ancestor(int u, int v) {
  return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
  if (is_ancestor(u, v)) {
    return u;
  }

  if (is_ancestor(v, u)) {
    return v;
  }

  per(i, l) {
    if (is_ancestor(up[u][i], v))
      continue;
    u = up[u][i];
  }

  return up[u][0];
}

int max_tree(int u, int v) {
  int ret = 0;

  int uu = u;
  per(i, l) {
    if (is_ancestor(up[uu][i], v))
      continue;

    ret = max(ret, upmax[uu][i]);

    dbg(ret);

    uu = up[uu][i];
  }

  int vv = v;
  per(i, l) {
    if (is_ancestor(up[vv][i], u))
      continue;
    ret = max(ret, upmax[vv][i]);

    dbg(ret);

    vv = up[vv][i];
  }

  // ret = max(ret, max(upmax[uu][0], upmax[vv][0]));

  if (up[uu][0] == v) {
    ret = max(ret, upmax[uu][0]);
  } else if (up[vv][0] == u) {
    ret = max(ret, upmax[vv][0]);
  } else {
    ret = max(ret, max(upmax[uu][0], upmax[vv][0]));
  }

  dbg(u, v, ret);

  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, q;
  cin >> n >> m >> q;

  vector<tuple<int, int, int>> edg;
  adj.resize(n);
  adj_tree.resize(n);

  dbg(n, m, q);

  rep(i, m) {
    int u, v, s;
    cin >> u >> v >> s;
    u--;
    v--;

    dbg(u, v, s);

    edg.emplace_back(s, u, v);

    adj[u].emplace_back(v, s);
    adj[v].emplace_back(u, s);
  }

  dbg(adj);

  // NOTE: We will read in the queries later, now we'll construct the MST

  UF uf(n);

  sort(edg.begin(), edg.end());

  for (auto &e : edg) {
    auto [s, u, v] = e;
    if (uf.sameSet(u, v))
      continue;
    adj_tree[u].emplace_back(v, s);
    adj_tree[v].emplace_back(u, s);
    uf.join(u, v);
  }

  for (auto &i : adj_tree) {
    dbg(i);
  }

  l = ceil(log2(n));

  dbg(l);

  up.resize(n, vector<int>(l + 1, 0));
  upmax.resize(n, vector<int>(l + 1, 0));

  tin.resize(n, 0);
  tout.resize(n, 0);

  dfs(0, 0, 0);

  dbg(up);
  dbg(upmax);

  rep(i, q) {
    int a, b, f, k, l;
    cin >> a >> b >> f >> k >> l;

    dbg(a, b, f, k, l);

    a--;
    b--;

    // compute ans and clamp it to [0, f];
    int ans = min(max(f - (max_tree(a, b) - l + k - 1) / k, 0), f);

    dbg(ans);

    cout << ans << '\n';
  }
}
