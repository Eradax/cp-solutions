#include <bits/stdc++.h>
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

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vpl nums;

  for (int i = 0; i < n; i++) {
    ll a, b;
    cin >> a >> b;

    nums.emplace_back(a, b);
  }

  sort(nums.begin(), nums.end(), [](pl a, pl b) {
    return (a.fi - 1) * b.se < (b.fi - 1) * a.se;
  });

  auto solve = [](auto nums, auto queries) {
    int n = sz(nums);
    int q = sz(queries);

    vvl dp(n + 1, vl(n + 1));

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        dp[i + 1][j + 1] = min(max(dp[i][j + 1], dp[i][j] * nums[i].fi + nums[i].se), MAX);
      }
    }

    vl out(q);

    for (int i = 0; i < q; i++) {
      ll k = queries[i];

      int ans = 0;
      while (ans < n + 1 && dp[n][ans] < k) ans++;
      out[i] = ans <= n ? ans : -1;
    }

    return out;
  };

  vector<ll> queries(q);
  for (auto& i : queries)
    cin >> i;

  auto res = solve(nums, queries);
  for (auto i : res)
    cout << i << ' ';
  cout << '\n';
}
