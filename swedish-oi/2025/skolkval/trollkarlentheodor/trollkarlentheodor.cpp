#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;

#define int ll
#define rep(i, n) for (int i = 0; i < (n); i++)

signed main() {
  int n, s, a;
  cin >> n >> s >> a;

  vector<int> h(n);
  rep(i, n) cin >> h[i];

  int lo = 0;
  int hi = a > 0 ? 2e10 / a : 2e10;

  while (lo < hi) {
    int mi = lo + (hi - lo) / 2;

    int ac = mi * a;

    int moves = 0;
    rep(i, n) {
      if (h[i] <= ac)
        continue;

      moves += (h[i] - ac + s - 1) / s;
    }

    dbg("-----", mi, moves);

    if (moves <= mi) {
      hi = mi;
    } else {
      lo = mi + 1;
    }
  }

  cout << lo << endl;
}
