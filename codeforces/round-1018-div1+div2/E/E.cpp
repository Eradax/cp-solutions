#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    int lb = -1;

    int ans = 0;

    for (int i = 0; i < n; i++) {
      char c;
      cin >> c;
      if (c == 'P') continue;

      ans += (i - lb - 1 + 1) / 2;
      lb++;
    }

    cout << ans << '\n';
  }
}
