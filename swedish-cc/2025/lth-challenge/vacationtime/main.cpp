#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define int ll

const int INF = 1e18;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vector<int> dist[2];
  dist[0].resize(n, INF);
  dist[1].resize(n, INF);

  vector<vector<tuple<int, int, int>>> adj(n);
  for (int i = 0; i < m; i++) {
    int o, d, c;
    string m;
    cin >> o >> d >> c >> m;
    int k = m == "A380";
    adj[o].emplace_back(d, c, k);
  }

  priority_queue<tuple<int, int, int>> pq;
  dist[0][0] = 0;

  pq.emplace(-0, 0, 0);
  while (!pq.empty()) {
    auto [w, u, b] = pq.top();
    pq.pop();

    w = -w;

    for (auto [v, vw, vb] : adj[u]) {
      if (dist[max(vb, b)][v] > w + vw) {
        dist[max(vb, b)][v] = w + vw;
        pq.emplace(-(w + vw), v, max(vb, b));
      }
    }
  }

  cout << (dist[1][n-1] < INF ? dist[1][n-1] : -1) << endl;
}
