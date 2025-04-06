#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())

using ll = long long;
using vl = vector<ll>;

using vi = vector<int>;
using vvi = vector<vi>;

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}

  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool sameset(int u, int v) { return find(u) == find(v); }
  int size(int x) { return -e[find(x)]; }
  bool join(int u, int v) {
    u = find(u);
    v = find(v);

    if (u == v)
      return 0;

    if (e[u] > e[v])
      swap(u, v);

    e[u] += e[v];
    e[v] = u;

    return 1;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vl a(n);
  for (auto& i : a)
    cin >> i;

  vvi mst(n);

  auto getMST = [&]() {
    vector<tuple<ll, int, int>> edges;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        ll w = a[i] ^ a[j];
        edges.emplace_back(w, i, j);
      }
    }

    ll ans = 0;
    sort(edges.rbegin(), edges.rend());
    UF uf(n);
    for (auto [w, u, v] : edges) {
      if (uf.sameset(u, v))
        continue;

      uf.join(u, v);
      mst[u].push_back(v);
      mst[v].push_back(u);
      ans += w;
    }

    return ans;
  };

  ll ans = getMST();

  vi ord, comb;

  auto getFromMST = [&]() {
    vi link(n, -1);
    function<void(int, int)> dfs = [&](int u, int p) {
      dbg(u, p);
      for (auto v : mst[u]) {
        if (v == p)
          continue;
        dfs(v, u);
      }

      for (auto it = mst[u].rbegin(); it != mst[u].rend(); it++) {
        int v = *it;
        if (v == p)
          continue;
        dbg(u, v);
        comb.push_back(link[v]);
      }

      link[u] = sz(ord);
      ord.push_back(u);
    };

    dfs(0, 0);
  };

  getFromMST();

  cout << ans << '\n';
  for (auto i : ord)
    cout << i << ' ';
  cout << '\n';
  for (auto i : comb)
    cout << i << ' ';
  cout << '\n';
}
