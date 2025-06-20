#include <bits/stdc++.h>
#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif
using namespace std;

using ll = long long;

vector<int> nxt;
vector<int> dep;
vector<int> vis;
vector<int> dp;
int dfs(int u, int d) {
  if (vis[u] == 2) {
    return dp[u];
  }
  if (vis[u] == 1) {
    int l = d - dep[u];

    dp[u] = l;
    vis[u] = 2;
    for (int v = nxt[u]; v != u; v = nxt[v]) {
      vis[v] = 2;
      dp[v] = l;
    }
    
    return dp[u];
  }

  dep[u] = d;
  vis[u] = 1;

  int v = nxt[u];

  if (v == -1) {
    dp[u] = 1;
    vis[u] = 2;
    return dp[u];
  }

  int tmp = dfs(v, d + 1);
  if (dp[u] == 0)
    dp[u] = 1 + tmp;

  vis[u] = 2;

  return dp[u];
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  nxt.resize(n, -1);
  dep.resize(n, -1);
  vis.resize(n, 0);
  dp.resize(n, 0);


  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;

    int ip = i + v;

    if (ip < 0 || ip >= n)
      continue;

    nxt[i] = ip;
  }

  dbg(nxt);

  for (int i = 0; i < n; i++)
    if (vis[i] == 0)
      dfs(i, 0);

  dbg(dp);

  ll ans = 0;
  for (auto i : dp)
    ans += i;

  cout << ans << endl;
}
