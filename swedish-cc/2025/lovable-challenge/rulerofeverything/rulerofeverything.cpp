#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

#define fi first
#define se second

using ll = long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

const ll MAX = 8e9 + 1;
const ll INF = 1e18;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  auto solve = [](auto nums, auto start, auto dim) {
    int n = sz(nums);
    vvl dp(n + 1, vl(dim + 1));
    dp[0][0] = start;

    for (int i = 0; i < n; i++) {
      dp[i + 1][0] = dp[i][0];
      for (int j = 0; j < dim; j++) {
        dp[i + 1][j + 1] = min(max(dp[i][j + 1], dp[i][j] * nums[i].fi + nums[i].se), MAX);
      }
    }

    return dp;
  };

  vpl lin, fst;

  for (int i = 0; i < n; i++) {
    ll a, b;
    cin >> a >> b;

    if (a == 1)
      lin.emplace_back(a, b);
    else
      fst.emplace_back(a, b);
  }

  sort(lin.rbegin(), lin.rend());
  sort(fst.begin(), fst.end(), [](pl a, pl b) {
    return (a.fi - 1) * b.se < (b.fi - 1) * a.se;
  });

  vl queries(q);
  for (auto& i : queries)
    cin >> i;

  ll ma = 0;
  for (auto i : lin)
    if (ma < MAX)
      ma = ma * i.fi + i.se;

  for (auto i : fst)
    if (ma < MAX)
      ma = ma * i.fi + i.se;

  ll ma2 = (sz(lin) ? lin[0].se : 0);
  for (auto i : fst)
    if (ma2 < MAX)
      ma2 = ma2 * i.fi + i.se;

  dbg(ma, ma2);

  if (ma2 >= MAX) {
    lin.resize(min(sz(lin), 35));

    vpl nums = lin;
    nums.insert(nums.end(), fst.begin(), fst.end());

    auto dp = solve(nums, 0, 35);
    vl res(q);
    for (int i = 0; i < q; i++) {
      ll ans = 0;
      while (ans < sz(dp[0]) && dp.back().at(ans) < queries[i]) ans++;
      res[i] = ans < sz(dp[0]) ? ans : INF;
    }

    for (auto i : res)
      cout << (i < INF ? i : -1) << ' ';
    cout << '\n';
  } else {
    ll pref = 0;
    auto dp = solve(fst, pref, n);
    dbg(dp);

    for (int i = 0; i < sz(lin); i++) {
      pref += lin[i].second;
      auto tmp = solve(fst, pref, sz(fst));
      for (int j = 0; j < sz(fst) + 1; j++) {
        for (int k = 0; k < sz(fst) + 1; k++) {
          dp[j][k + i + 1] = max(dp[j][k + i + 1], tmp[j][k]);
        }
      }

      dbg(i, pref, tmp, dp);
    }

    vl ans(q);
    for (int i = 0; i < q; i++) {
      int lo = 0;
      int hi = n + 1;

      while (lo + 1 < hi) {
        int mi = lo + (hi - lo) / 2;

        if (dp.back().at(mi) >= queries[i]) {
          hi = mi;
        } else {
          lo = mi;
        }
      }

      ans[i] = hi <= n ? hi : INF;
    }

    for (auto i : ans)
      cout << (i < INF ? i : -1) << ' ';
    cout << '\n';
  }
}
