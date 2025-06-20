#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (auto& i : a) cin >> i;

  auto mgcd = [](vector<int>& v) {
    int ans = v[0];
    for (auto i : v) ans = gcd(ans, i);

    return ans;
  };

  if (n >= 8) {
    cout << (mgcd(a) > 1) << endl;
    return 0;
  }

  auto solve = [mgcd, n](auto self, vector<int> v, int us, int s) {
    if (mgcd(v) == 1) return 1;
    if (s == n) return 0;

    for (int i = 0; i <= us; i++) {
      v[s] += i;
      if (self(self, v, us - i, s + 1)) return 1;
      v[s] -= i;
    }

    return 0;
  };

  int ans = 0;
  while (!solve(solve, a, ans, 0)) ans++;

  cout << ans << endl;
}
