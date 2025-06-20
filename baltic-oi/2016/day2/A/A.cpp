#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
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


template<typename T, typename U> ostream& operator<<(ostream& o, pair<T, U> v) {
  o << "{ ";
  o << v.first << ", " << v.second;
  o << "}";
  return o;
}

template<typename T> ostream& operator<<(ostream& o, vector<T> v) {
  o << "{ ";
  for (auto& i : v) o << i << ", ";
  o << "}";
  return o;
}

template<typename T> ostream& operator<<(ostream& o, vector<vector<T>> v) {
  o << "{ ";
  for (auto& i : v) o << i << ", ";
  o << "}";
  return o;
}

const int INF = 3e18;

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;

signed main() {
  int n, k, m;
  cin >> n >> k >> m;

  dbg(n);
  dbg(k);
  dbg(m);

  vi imp(k);
  for (auto& i : imp) {
    cin >> i, i--;
  }

  dbg(imp);

  vector<vector<pair<int, int>>> adj(n);
  for (int i = 0; i < m; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].emplace_back(b, c);
    adj[b].emplace_back(a, c);
  }

  dbg(adj);

  vvi dp(1<<k, vi(n, INF));
  priority_queue<tuple<int, int, int>> pq;
  for (int i = 0; i < k; i++) {
    dp[1 << i][imp[i]] = 0;
    pq.emplace(-0, 1 << i, imp[i]);
  }
  
  while (sz(pq)) {
    auto [w, mask, u] = pq.top();
    pq.pop();
    w = -w;

    dbg(w);
    dbg(mask);
    dbg(u);

    for (int nmask = ((1<<k)-1)^mask; nmask; nmask = (nmask-1)&(((1<<k)-1)^mask)) {
      int comb = mask | nmask;
      if (dp[comb][u] <= dp[mask][u] + dp[nmask][u]) continue;
      dp[comb][u] = dp[mask][u] + dp[nmask][u];
      pq.emplace(-dp[comb][u], comb, u);
    }

    for (auto [v, vw] : adj[u]) {
      if (dp[mask][v] <= w + vw) continue;
      dp[mask][v] = w + vw;

      pq.emplace(-dp[mask][v], mask, v);
    }
  }

  ll ans = INF;
  for (int i = 0; i < n; i++) {
    ans = min(ans, dp[(1 << k) - 1][i]);
  }

  cout << ans << endl;
}
