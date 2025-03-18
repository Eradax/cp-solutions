#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> a(n), dp(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  if (n == 1) {
    cout << a[0] << endl;
    return 0;
  }

  dp[0] = a[0];
  dp[1] = a[0] + a[1];
  for (int i = 2; i < n; i++) {
    dp[i] = a[i] + min(dp[i - 1], dp[i - 2]);
  }

  cout << dp[n - 1] << endl;
}
