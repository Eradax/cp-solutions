#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>

using namespace std;

typedef long long ll;

typedef vector<ll> vi;
typedef vector<vi> vvi;

typedef pair<ll, ll> p2;
typedef vector<p2> vp2;
typedef vector<vp2> vvp2;

#define repe(i, c) for (auto& i : c)
#define sz(c) ((int)c.size())

ll INF = 1e18;

struct Line {
  ll start, end, first, cycle, length;

  Line(ll start, ll end, ll first, ll cycle, ll length)
      : start(start), end(end), first(first), cycle(cycle), length(length) {}
};

vector<vector<Line>> adj;

ll waitTime(ll time, p2 timeinfo) {
  if (time <= timeinfo.first) {
    return timeinfo.first - time;
  } else {
    ll firstTrain = time - timeinfo.first;
    ll lastTrain = firstTrain % timeinfo.second;

    return (lastTrain == 0) ? 0 : (timeinfo.second - lastTrain);
  }
}

ll djikstra(ll t) {
  int s = 0;
  int n = sz(adj);
  vi seen(n);
  vi dist(n, INF);
  dist[s] = t;
  ll di;

  __gnu_pbds::priority_queue<pair<ll, int>> q;
  vector<decltype(q)::point_iterator> its(n);
  q.push({t, s});

  while (!q.empty()) {
    s = q.top().second;
    q.pop();
    seen[s] = 1;
    di = dist[s];
    repe(e, adj[s]) if (!seen[e.first]) {
      ll val = di + e.length + waitTime(di, {e.first, e.cycle});
      if (val < dist[e.end]) {
        dist[e.end] = val;
        if (its[e.end] == q.end())
          its[e.end] = q.push({-dist[e.end], e.end});
        else
          q.modify(its[e.end], {-dist[e.end], e.end});
      }
    }
  }

  return dist[n - 1];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  ll n, m, s;
  cin >> n >> m >> s;
  adj.resize(n);

  for (int i = 0; i < m; i++) {
    ll start, end, first, cycle, length;
    cin >> start >> end >> first >> cycle >> length;

    adj[start].emplace_back(start, end, first, cycle, length);
  }

  ll lo = 0, hi = s;
  while (lo < hi) {
    ll mi = (lo + hi + 1) / 2;
    if (djikstra(mi) > s) {
      hi = mi - 1;
    } else {
      lo = mi;
    }
  }

  if (djikstra(lo) <= s) {
    cout << lo << endl;
  } else {
    cout << "impossible" << endl;
  }
}
