#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:
    Chalmers Challenge 2024
links:
    https://open.kattis.com/problems/gymaesthetics
*/

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()
#define rall(c) c.rbegin(), c.rend()
#define sz(c) ((int)c.size())

int len(int a) {  // sizeof(int) - clz(a)
  int ans = 0;

  while (a >= (1 << ans)) {
    ans++;
  }

  return ans;
}

int add_cost(int a) {  // popcnt
  int ans = 0;
  rep(i, len(a)) {
    ans += (a & (1 << i)) > 0;
  }

  return ans;
}

int lcp(int a, int b) {
  int l = 0;
  int ans = 0;
  while (((a & (1 << l)) == (b & (1 << l))) && l <= min(len(a), len(b))) {
    ans += (a & (1 << l)) > 0;
    l++;
  }

  return ans;
}

int cost(int a, int b) {
  return add_cost(a) + add_cost(b) - 2 * lcp(a, b);
}

vi v, w;
int weight(int s) {
  int ans = 0;
  rep(i, len(s)) {
    if (s & (1 << i)) {
      ans += w[i];
    }
  }

  return ans;
}

// dp[i][mask] = minimim number of moves to endup with after having done the
// first `i` lifts and have `mask` left on the bar. This implies that the
// answer should be `dp[n][0]`.

// dp[0][mask] = popcnt(mask);
// dp[i][mask] = min(dp[i - 1][mask2] + popcnt(mask) + popcnt(mask2) -
// same(mask, mask2))
vvi dp;
int n, k;
int solve(int i, int mask) {
  if (dp[i][mask] != -1) {
    return dp[i][mask];
  }

  if (weight(mask) != v[i]) {
    return dp[i][mask] = INF;
  }

  if (i == 0) {
    return dp[i][mask] = add_cost(mask);
  }

  int ans = INF;

  rep(s, 1 << k) {
    if (solve(i - 1, s) == -1)
      continue;

    ans = min(ans, solve(i - 1, s) + cost(mask, s));

    if (ans == -1) {
      dbg(i, mask, ans, s, solve(i - 1, s), cost(mask, s));
    }
  }

  return dp[i][mask] = ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> k;

  v.resize(n);
  rep(i, n) {
    cin >> v[i];
  }
  rep(i, n) {
    v[i] = v[i] / 20 - 1;
  }

  w.resize(k);
  rep(i, k) {
    cin >> w[i];
  }
  rep(i, k) {
    w[i] /= 10;
  }

  sort(rall(w));

  dp.resize(n + 1, vi(1LL << k, -1));

  int ans = INF;

  rep(s, 1 << k) {
    if (solve(n - 1, s) == -1)
      continue;

    ans = min(ans, solve(n - 1, s) + cost(0, s));
  }

  // rep(i, n) {
  //   rep(j, sz(dp[i])) {
  //     if (dp[i][j] != INF) {
  //       cout << "{ " << j << ": " << dp[i][j] << "}\t";
  //     }
  //   }
  //
  //   cout << endl;
  // }

  cout << ans << endl;
}
