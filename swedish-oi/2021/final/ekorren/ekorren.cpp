#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)

using vi = vector<int>;
using vvi = vector<vi>;

vvi adj;
vector<bool> nut;

int dfs(int u, int p) {
  int ans = 0;
  for (auto e : adj[u]) {
    if (e == p)
      continue;
    ans += dfs(e, u);
  }

  if (u != 0 && (ans || nut[u]))
    ans++;

  dbg(u, p, ans);

  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;

  cin >> n >> k;

  adj.resize(n);
  nut.resize(n);

  rep(i, k) {
    int t;
    cin >> t;
    t--;
    nut[t] = 1;
  }

  rep(i, n - 1) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  int ret = 2 * dfs(0, -1);

  cout << ret << '\n';
}
