#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
// #pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

#ifdef DBG
  #define dbg(expr)                                                          \
    cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
         << expr << endl;
#else
  #define dbg(...)
#endif

ostream& operator<<(ostream& o, vector<int> v) {
  o << "{";
  for (auto i : v)
    o << i << ", ";
  o << "}";
  return o;
}

const int INF = 1e9;

const int V2 = 40;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }

  vector<vector<int>> dp(n, vector<int>(V2, -1));
  for (int i = 0; i < n; i++) {
    for (int j = a[i]; j < V2; j++)
      dp[i][j] = i;
  }

  for (int i = 0; i < n; i++) {
    dbg(i);
    dbg(dp[i]);
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = 1; j < V2; j++) {
      int nod = dp[i][j - 1];
      if (nod == -1) continue;
      if (nod == n-1) {
        dp[i][j] = n-1;
        continue;
      }

      int nnod = dp[nod+1][j - 1];

      if (nnod == -1) {
        dp[i][j] = max(dp[i][j], nod);
        continue;
      }

      dp[i][j] = max(dp[i][j], nnod);
    }
  }

  for (int i = 0; i < n; i++) {
    dbg(i);
    dbg(dp[i]);
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    int ans = -1;
    for (int j = 0; j < V2; j++) {
      if (dp[l][j] >= r) {
        ans = j;
        break;
      }
    }

    cout << ans << '\n';
  }
}
