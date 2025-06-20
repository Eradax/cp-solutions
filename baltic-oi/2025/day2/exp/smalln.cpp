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

const int V2 = 60;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }

  vector<vector<int>> dp(n, vector<int>(n, INF));
  for (int i = 0; i < n; i++) {
    dp[i][i] = a[i];
  }

  for (int i = 0; i < n; i++) {
    dbg(i);
    dbg(dp[i]);
  }

  for (int len = 2; len <= n; len++) {
    for (int l = 0, r = len-1; r < n; l++, r++) {
      for (int m = l; m < r; m++) {
        dp[l][r] = min(dp[l][r], 1 + max(dp[l][m], dp[m+1][r]));
      }
    }
  }

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    int ans = dp[l][r];

    cout << ans << '\n';
  }
}
