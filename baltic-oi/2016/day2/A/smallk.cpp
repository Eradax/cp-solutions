#include <bits/stdc++.h>
#include <queue>
using namespace std;

#define check(a, b) ((a >> b) & 1)
#define sz(c) ((int)c.size())

#ifdef DBG
#define dbg(expr) cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " << expr << endl;
#else
#define dbg(...)
#endif

using ll = long long;
#define int ll

const int INF = 3e18;

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;

struct UF {
  vi e;
  UF(int n) : e(n, -1) {}
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return 0;

    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b];
    e[b] = a;

    return 1;
  }
};

void dijkstra(int s, vector<vector<pi>>& adj, vi& dist) {
  int n = sz(adj);
  dist.resize(n, INF);

  priority_queue<pi> pq;
  pq.emplace(-0, s);
  dist[s] = 0;
  while (sz(pq)) {
    auto [w, u] = pq.top();
    pq.pop();
    w = -w;

    if (dist[u] < w) continue;

    for (auto [v, vw] : adj[u]) {
      if (dist[v] <= w + vw) continue;
      dist[v] = w + vw;
      pq.emplace(-dist[v], v);
    }
  }
}

signed main() {
  int n, k, m;
  cin >> n >> k >> m;

  dbg(n);
  dbg(k);
  dbg(m);

  vi imp(k);
  int choice_num = 0;
  for (auto& i : imp) {
    cin >> i, i--;
    choice_num |= 1 << i;
  }

  dbg(choice_num);

  vector<vector<pair<int, int>>> adj(n);
  vector<tuple<int, int, int>> edg;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  if (k == 2) {
    vi dists;
    dijkstra(imp[0], adj, dists);
    cout << dists[imp[1]] << endl;
    return 0;
  }

  assert(k == 3);

  ll best = INF;

  vi d0, d1, d2;
  dijkstra(imp[0], adj, d0);
  dijkstra(imp[1], adj, d1);
  dijkstra(imp[2], adj, d2);

  for (int source = 0; source < n; source++) {
    ll ans = d0[source] + d1[source] + d2[source];
    best = min(ans, best);
  }

  cout << best << endl;
}
