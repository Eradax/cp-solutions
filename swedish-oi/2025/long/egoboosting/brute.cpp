#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

static const int INF = 1e9 + 100;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, e;
  cin >> n >> e;

  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  auto check = [&](int u) {
    dbg(u);
    int cost = 0;
    int mye = e;

    int l = u;
    int r = u;

    cost += max(a[u] - mye, 0);
    mye += cost + 1;

    dbg(mye, cost);

    while (0 < l || r < n - 1) {
      dbg("----------------");
      dbg(l, r, mye, cost);
      if (0 < l && a[l - 1] <= mye) {
        l--;
        mye++;
      } else if (r < n - 1 && a[r + 1] <= mye) {
        r++;
        mye++;
      } else {
        int cheap = INF;
        if (0 < l)
          cheap = min(cheap, a[l - 1]);
        if (r < n - 1)
          cheap = min(cheap, a[r + 1]);

        cost += cheap - mye;
        mye = cheap;
      }

      dbg(l, r, mye, cost);
    }

    dbg(cost);
    return cost;
  };

  int ans = INF;
  for (int i = 0; i < n; i++) {
    ans = min(ans, check(i));
  }

  cout << ans << endl;
}
