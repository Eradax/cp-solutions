#include <bits/stdc++.h>
// #include "../../../dbg.h"
#define dbg(...)
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    dbg(n);

    vector<pair<int, int>> a(n);
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
      cin >> a[i].first;
      a[i].first *= -1;
      a[i].second = i;
      b[i] = -a[i].first;
    }

    sort(a.begin(), a.end());

    dbg(a);

    int ans = 0;

    int i = 0;
    int j = 0;

    while (j < n) {
      dbg(i, j);
      while (j < n && a[i].first == a[j].first &&
             a[i].second + j - i == a[j].second)
        j++;

      dbg(i, j);

      dbg((a[i].second - 1 >= 0 && b[a[i].second - 1] >= -a[i].first));
      dbg((a[j - 1].second + 1 < n && b[a[j - 1].second + 1] >= -a[i].first));

      ans += !(
          (a[i].second - 1 >= 0 && b[a[i].second - 1] >= -a[i].first) ||
          a[j - 1].second + 1 < n && b[a[j - 1].second + 1] >= -a[i].first
      );

      i = j;
      j = i;
    }

    cout << ans << '\n';
  }
}
