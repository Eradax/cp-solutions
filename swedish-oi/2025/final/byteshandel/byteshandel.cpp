#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = long long;

#define int ll

using pi = pair<int, int>;

using vpi = vector<pi>;
using vvpi = vector<vpi>;

using vi = vector<int>;
using vvi = vector<vi>;

static constexpr int INF = 1e18;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define setcontains(c, x) (c.find(x) != c.end())

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vvi adj(n);

  vvpi ex;

  rep(j, m) {
    int ri, ki;
    cin >> ri >> ki;

    vpi vals(ki);
    rep(i, ki) {
      cin >> vals[i].first >> vals[i].second;
      adj[vals[i].second].push_back(j);
    }
    vals.emplace_back(ri, ki);

    ex.push_back(vals);
  }

  dbg(adj, ex);

  for (auto e : ex) {
    dbg(e);
  }

  int s;

  vi seen(n);
  vi dist(n, INF);

  dist[0] = 1;
  ll di;

  __gnu_pbds::priority_queue<pair<ll, int>> q;
  vector<decltype(q)::point_iterator> its(n);

  q.push({1, 0});

  while (!q.empty()) {
    s = q.top().second;
    q.pop();

    dbg(s);
    dbg(q);

    seen[s] = 1;
    di = dist[s];

    for (auto e : adj[s]) {
      vpi* edge = &ex[e];

      dbg(edge);

      dbg(edge->back().second);
      edge->back().second--;
      dbg(edge->back().second);

      if (seen[edge->back().first]) {
        continue;
      }

      if (edge->back().second > 0) {
        continue;
      }

      ll weight = 0;
      rep(i, (int)edge->size() - 1) {
        weight += edge->at(i).first * dist[edge->at(i).second];
      }

      ll val = weight;

      if (val < dist[edge->back().first]) {
        dist[edge->back().first] = val;

        if (its[edge->back().first] == q.end()) {
         its[edge->back().first] = q.push({-val, edge->back().first});
        } else {
          q.modify(its[edge->back().first], {-val, edge->back().first});
        }
      }
    }
  }

  dbg(dist);

  cout << dist[n-1] << endl;
}
