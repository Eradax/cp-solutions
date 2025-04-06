#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;

#define sz(c) ((int)c.size())

pair<ll, ll> getTakes(ll x, ll y) {
  ll c = 0;
  ll num = x;

  ll take = 0;

  ll doub = -1;

  ll i = 1;

  while (num) {
    if (c + num <= y) {
      dbg(num, i);
      c += num;
      take |= i;
    }

    if (c + num == y) {
      c += num;
      doub = num;
      break;
    }
    num /= 2;
    i <<= 1;
  }

  dbg(c);

  return {take >> 1, doub};
}

pair<int, vector<pair<int, int>>> decouple(vector<pair<int, int>> e) {
  set<int> nodes;
  map<int, int> trans;
  for (auto [u, v] : e) {
    if (nodes.count(u) == 0)
      nodes.insert(u);

    if (nodes.count(v) == 0)
      nodes.insert(v);
  }

  for (auto i : nodes) {
    trans[i] = sz(trans);
  }

  dbg(nodes);

  int n = sz(nodes);
  vector<pair<int, int>> ne;
  for (auto [u, v] : e) {
    ne.emplace_back(trans[u], trans[v]);
  }

  dbg(ne);

  return {n, ne};
}

vector<pair<int, int>> cleanup(vector<pair<int, int>> e) {
  set<int> nodes;
  map<int, vector<int>> adj;
  for (auto [u, v] : e) {
    if (nodes.count(u) == 0)
      nodes.insert(u);

    if (nodes.count(v) == 0)
      nodes.insert(v);

    adj[u].push_back(v);
  }

  int scrap = 1e5;
  int en = *nodes.rbegin();
  assert(nodes.count(scrap) == 0);

  map<int, int> vis;
  map<int, int> isScrap;
  function<void(int)> dfs = [&](int u) {
    vis[u] = 1;

    if (sz(adj[u]) == 0) {
      isScrap[u] = u != en;
      return;
    }

    bool meScrap = 1;

    for (auto v : adj[u]) {
      if (!vis[v]) dfs(v);
      meScrap &= isScrap[v];
    }

    isScrap[u] = meScrap;
  };

  for (auto i : nodes) if (!vis[i]) dfs(i);

  dbg(e, isScrap);

  vector<int> scraps = {scrap};
  set<pair<int, int>> sed;
  for (auto [u, ad] : adj) {
    if (isScrap[u]) continue;
    for (auto v : ad) {
      if (isScrap[v]) {
        bool succ = 0;
        for (auto s : scraps) {
          if (sed.count({u, s})) continue;
          sed.emplace(u, s);
          succ = 1;
          break;
        }
        if (!succ) {
          sed.emplace(u, ++scrap);
          scraps.push_back(scrap);
        }
      } else {
        sed.emplace(u, v);
      }
    }
  }

  vector<pair<int, int>> ne(sed.begin(), sed.end());
  return ne;
}



int main() {
  ll x, y;
  cin >> x >> y;

  if (y > x) {
    cout << -1 << endl;
    return 0;
  }

  if (x == y) {
    cout << "2 1" << '\n';
    cout << "1 2" << '\n';
    return 0;
  }

  dbg(x, y);

  auto [take, doub] = getTakes(x, y);

  dbg(take, doub);

  int n = 1e6;
  int sink = n - 3;

  dbg(n, sink);

  vector<pair<int, int>> edg;

  edg.emplace_back(n - 2, n - 1);

  int i = 0;
  while (x > 0) {
    dbg(x, doub, take, i);
    if (x>>1 == doub) {
      edg.emplace_back(i, n - 1);
      edg.emplace_back(i, n - 2);
    } else if (take & 1) {
      edg.emplace_back(i, i + 1);
      edg.emplace_back(i, n - 1);
    } else {
      edg.emplace_back(i, i + 1);
      edg.emplace_back(i, sink);
    }

    take >>= 1;
    x >>= 1;
    i++;
  }

  dbg(edg);

  edg = cleanup(edg);
  tie(n, edg) = decouple(edg);

  dbg(n, edg);

#ifdef DBG
  cout << n << " " << sz(edg) << '\n';
  for (auto [u, v] : edg) {
    cout << u + 1 << " -> " << v + 1 << '\n';
  }
#else
  cout << n << " " << sz(edg) << '\n';
  for (auto [u, v] : edg) {
    cout << u + 1 << " " << v + 1 << '\n';
  }
#endif
}
