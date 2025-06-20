#include <bits/stdc++.h>
#ifdef DBG
  #include "/home/eradax/persist/cp/cp-solutions/dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define sz(c) ((int)c.size())

mt19937 rng;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  map<double, int> ma;

  vector<int> a;
  vector<vector<int>> pos(n);
  for (int i = 0; i < n; i++) {
    double v;
    cin >> v;

    if (ma.count(v) == 0)
      ma[v] = sz(ma);
    a.push_back(ma[v]);
    pos[ma[v]].push_back(i);
  }

  dbg(a, ma);

  for (int i = 0; i < m; i++) {
    int l, r;
    cin >> l >> r;
    l--, r--;

    bool flag = 0;

    for (int j = 0; j < 30 && !flag; j++) {
      int idx = uniform_int_distribution<int>(l, r)(rng);
      int val = a[idx];

      auto low = lower_bound(pos[val].begin(), pos[val].end(), l);
      auto hig = upper_bound(pos[val].begin(), pos[val].end(), r);
      int len = hig - low;

      dbg(idx, val, pos[val], l, r, len);

      if (len >= 1 + (r - l + 1) / 2)
        flag = 1;
    }

    if (flag) {
      cout << "usable" << '\n';
    } else {
      cout << "unusable" << '\n';
    }
  }
}
