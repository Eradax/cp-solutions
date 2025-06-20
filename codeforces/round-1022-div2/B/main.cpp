#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n, x;
    cin >> n >> x;

    if (n == 1 && x == 0) {
      cout << -1 << '\n';
      continue;
    }

    int ans = x;
    int cnt = __builtin_popcount(x);
    if (cnt < n) {
      int tolose = n - cnt;
      ans += (tolose / 2 * 2);
      tolose %= 2;

      if (cnt >= 2) ans += 2 * tolose;
      else if (cnt == 1 && (x&1)==0) ans += 2 * tolose;
      else ans += 4 * tolose; 
    }

    cout << ans << '\n';
  }
}
