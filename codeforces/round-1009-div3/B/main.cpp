#include <bits/stdc++.h>

using namespace std;

int main() {
  int t;
  cin >> t;
  while (t--) {
    int n, nn;
    cin >> n;
    nn = n;
    int ans = 0;
    while (nn--) {
      int a;
      cin >> a;

      ans += a;
    }
    ans -= n - 1;
    cout << ans << '\n';
  }
}
