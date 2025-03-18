#include <bits/stdc++.h>
using namespace std;

static const int MOD = 1e9+7;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> dp(n);

  dp[0] = 1;
  dp[1] = 2;
  for (int i = 2; i < n; i++) {
    dp[i] = (dp[i-1] + dp[i-2]) % MOD;
  }

  cout << dp[n - 1] << endl;
}
