#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i].first;
      a[i].second = i;
    }

    sort(a.rbegin(), a.rend());

    bool alls = 1;
    for (int i = 0; i < n-1; i++) alls &= a[i].first == a[i+1].first;

    if (alls) {
      cout << "No" << '\n';
      continue;
    }

    cout << "Yes" << '\n';
    vi ans(n);
    ans[a[0].second] = 1;
    for (int i = 1; i < n; i++) {
      auto [v, j] = a[i];
      ans[j] = 2;
    }
    for (int i = 0; i < n; i++) cout << ans[i] << ' ';
    cout << '\n';
  }
}
