#include <bits/stdc++.h>
using namespace std;

using ll = long long;

inline bool is_col(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3) {
  return (x2 - x1) * (y3 - y1) == (y2 - y1) * (x3 - x1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<pair<ll, ll>> pts(n);
  for (int i = 0; i < n; i++)
    cin >> pts[i].first >> pts[i].second;

  if (n == 2) {
    cout << "1 2\n";
    return 0;
  }

  bool ac = true;
  for (int k = 2; k < n; k++) {
    if (!is_col(
            pts[0].first,
            pts[0].second,
            pts[1].first,
            pts[1].second,
            pts[k].first,
            pts[k].second
        )) {
      ac = false;
      break;
    }
  }

  if (ac) {
    cout << "learning is guaranteed!" << '\n';
    return 0;
  }

  int i1 = 0, i2 = 1, i3 = -1;
  for (int k = 2; k < n; k++) {
    if (!is_col(
            pts[i1].first,
            pts[i1].second,
            pts[i2].first,
            pts[i2].second,
            pts[k].first,
            pts[k].second
        )) {
      i3 = k;
      break;
    }
  }

  array<pair<int, int>, 3> cand = {{{i1, i2}, {i1, i3}, {i2, i3}}};
  for (auto [a, b] : cand) {
    int cnt = 0;
    for (int k = 0; k < n; k++) {
      if (is_col(
              pts[a].first,
              pts[a].second,
              pts[b].first,
              pts[b].second,
              pts[k].first,
              pts[k].second
          )) {
        cnt++;
      }
    }
    if (cnt == 2) {
      cout << (a + 1) << " " << (b + 1) << '\n';
      return 0;
    }
  }

  cout << "Fuck" << endl;
}
