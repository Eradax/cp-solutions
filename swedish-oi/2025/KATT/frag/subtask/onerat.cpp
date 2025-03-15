// #pragma GCC optimize("Ofast")
// #include <bitset>
// #pragma GCC target("avx2")
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
#define sz(c) ((int)c.size())

using ll = long long;
#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static constexpr int INF = 1e18;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, t;
  cin >> n >> m >> t;

  assert(m == 1);

  vvpi adj(n);
  vi par(n);
  vi dists(n);
  vi dist0(n);
  vi end(n);

  rep(_, n - 1) {
    int a, b, ti;
    cin >> a >> b >> ti;
    adj[a].emplace_back(b, ti);
    adj[b].emplace_back(a, ti);
  }

  {
    function<void(int, int)> dfs;
    dfs = [&](int u, int p) {
      for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dist0[v] = w + dist0[u];
        dfs(v, u);
      }
    };
    dfs(0, -1);
  }

  {
    int e;

    function<void(int, int)> dfs;
    dfs = [&](int u, int p) {
      end[u] = e;
      par[u] = p;
      for (auto [v, w] : adj[u]) {
        if (v == p) continue;
        dists[v] = w + dists[u];
        dfs(v, u);
      }
    };

    par[0] = -1;

    for (auto [u, w] : adj[0]) {
      e = u;
      dists[u] = 0;
      dfs(u, 0);
    }
  }

  dbg(end);
  dbg(dist0);
  dbg(adj, par);
  dbg(dists);

  vi energy(n - 1);
  rep(i, n - 1) cin >> energy[i];

  vi rats(m);
  rep(i, m) cin >> rats[i];

  dbg(energy, rats);
   
  // vi done(n);
  // vi entr(n, INF);
  //
  // for (auto i : rats) {
  //   entr[end[i]] = min(entr[end[i]], dists[i]);
  // }
  //
  // dbg(entr);
  //
  // int ans = 0;
  // rep(i, n) {
  //   dbg(i, end[i], t - entr[end[i]] - dist0[end[i]]);
  //   if (done[end[i]]) continue;
  //   ans += max(t - entr[end[i]] - dist0[end[i]], 0LL);
  //   done[end[i]] = 1;
  // }
  
  int ans = INF;

  int node = rats[0];
  int d = max(t - dist0[node], 0LL);
  while (node != 0) {
    dbg(node, d, energy[node-1]);
    ans = min(ans, energy[node-1] * d);
    node = par[node];
  }

  cout << ans << endl;
}
