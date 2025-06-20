#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())
#define ge(v, i) (i >= 0 ? v[i] : 0)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  vector<double> dp(n * m + 1, 0);
  vector<double> pre(n * m + 1, 0);
  dp[0] = 1;

  for (int _ = 0; _ < n; _++) {
    pre[0] = dp[0];
    for (int i = 1; i < sz(dp); i++)
      pre[i] = pre[i - 1] + dp[i];

    for (int i = 0; i < sz(dp); i++)
      dp[i] = (ge(pre, i - 1) - ge(pre, i - m - 1)) / m;
  }

  sort(dp.rbegin(), dp.rend());

  double ans = 0;
  for (int i = 0; i < k; i++)
    ans += dp[i];

  cout << fixed << setprecision(5) << ans << endl;
}
