#pragma GCC optimize("O3")
#include <bits/allocator.h>
// #pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

  // #define dbg(expr)                                                          \
  //   cerr << "[" << __FUNCTION__ << ", " << __LINE__ << "] " << #expr << ": " \
  //        << expr << endl;
#ifdef DBG
  #include "../../../../dbg.h"
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

#define sz(c) ((int)c.size())

const int INF = 1e9;

const int MX = 1e7;
const int NL = __bit_width(MX) * 2;

using vi = vector<int>;
using vvi = vector<vi>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto& i : a) {
    cin >> i;
  }

  auto calc_dp = [](vvi& dp, vi a) {
    int n = sz(a);
    dp.assign(n, vi(NL, -1));

    dbg(n, dp);

    for (int i = 0; i < n; i++)
      for (int j = a[i]; j < NL; j++)
        dp[i][j] = i;

    for (int i = n - 1; i >= 0; i--) {
      for (int j = 1; j < NL; j++) {
        int nod = dp[i][j - 1];
        if (nod == -1)
          continue;

        dp[i][j] = nod;

        if (nod == n - 1)
          continue;

        int nxt_nod = dp[nod + 1][j - 1];

        if (nxt_nod == -1)
          continue;

        dp[i][j] = nxt_nod;
      }
    }
  };

  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    dbg(l, r);

    int mx = 0;
    for (int i = l; i <= r; i++)
      mx = max(mx, a[i]);
    int mn = max(mx - NL / 2 + 1, 0);
    vi b;
    for (int i = l; i <= r; i++)
      b.push_back(max(a[i] - mn, 0));

    vvi dp;
    calc_dp(dp, b);

    dbg(dp, b);

    r -= l;
    l -= l;

    dbg(l, r);

    int ans = -1;
    for (int j = 0; j < NL; j++) {
      if (dp[l][j] >= r) {
        ans = j;
        break;
      }
    }

    cout << ans + mn << '\n';
  }
}
