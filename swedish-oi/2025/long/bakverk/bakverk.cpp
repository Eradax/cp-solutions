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
#define int ll

const ll INF = 2e18;

#define sz(c) ((int)c.size())

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
      if (!vis[v])
        dfs(v);
      meScrap &= isScrap[v];
    }

    isScrap[u] = meScrap;
  };

  for (auto i : nodes)
    if (!vis[i])
      dfs(i);

  dbg(e, isScrap);

  vector<int> scraps = {scrap};
  set<pair<int, int>> sed;
  for (auto [u, ad] : adj) {
    if (isScrap[u])
      continue;
    for (auto v : ad) {
      if (isScrap[v]) {
        bool succ = 0;
        for (auto s : scraps) {
          if (sed.count({u, s}))
            continue;
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

signed main() {
  ll x, y;
  cin >> x >> y;

  ll xx = x, yy = y;
  if (y > x) {
    cout << -1 << endl;
    return 0;
  }

  dbg(x, y);

  vector<pair<int, int>> bed;
  int bn = 1e9;

  const int AAA = 20;
  const int BBB = 20;

  for (int maxAccum = 1; maxAccum <= AAA; maxAccum++) {
    for (int BB = 1; BB <= BBB; BB++) {
      int n = 1e9;
      int sink = 1e8;
      int maxSink = 0;
      int maxAcc = 0;

      x = xx, y = yy;
      dbg(n, sink, maxAccum);

      vector<pair<int, int>> edg;

      int i = 0;
      for (; y > 0 && x > 0; i++) {
        if (x == y) {
          edg.emplace_back(i, n);
          x -= x / 1;
          y += x / 1;

          continue;
        }

        dbg(x, y, maxAccum);

        int bestAccum = -1;
        ll bestAccumVal = INF;
        ll bestNyVal = INF;
        int bestAccumSinks = -1;
        for (int accums = 0; accums <= maxAccum; accums++) {
          for (int sinks = 0; sinks <= BB; sinks++) {
            ll nx = x / (accums + 1 + sinks);
            ll ny = y - accums * (x / (accums + 1 + sinks));

            if (ny >= 0 && ny - nx <= 0) {
              if (nx < bestAccumVal) {
                bestAccum = accums;
                bestAccumVal = nx;
                bestNyVal = ny;
                bestAccumSinks = sinks;
              }
            }
          }
        }

        dbg(x, y, bestAccum, bestAccumVal, bestAccumSinks);

        x = bestAccumVal;
        y -= bestAccum * bestAccumVal;

        dbg(x, y);

        if (x > 0 && x == y) {
          bestAccum++;
          y -= x;
          x = 0;
        } else {
          edg.emplace_back(i, i + 1);
        }
        for (int j = 0; j < bestAccum; j++)
          edg.emplace_back(i, n - j);
        maxAcc = max(maxAcc, bestAccum);

        for (int j = 0; j < bestAccumSinks; j++)
          edg.emplace_back(i, sink + j);
        maxSink = max(maxSink, bestAccumSinks);
      }

      dbg(maxAcc);

      for (int i = 1; i < maxAcc; i++)
        edg.emplace_back(n - i, n);

      dbg(edg);

      edg = cleanup(edg);
      int nn;
      tie(nn, edg) = decouple(edg);

      dbg(nn, edg);

      if (nn < bn) {
        bn = nn;
        bed = edg;
      }

      dbg(n, edg);
    }
  }

#ifdef DBG
  cout << bn << " " << sz(bed) << '\n';
  for (auto [u, v] : bed) {
    cout << u + 1 << " -> " << v + 1 << '\n';
  }
#else
  cout << bn << " " << sz(bed) << '\n';
  for (auto [u, v] : bed) {
    cout << u + 1 << " " << v + 1 << '\n';
  }
#endif
}
