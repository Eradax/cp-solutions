#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = long long;

#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

static constexpr int INF = 1e18;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vi ank(n);
  rep(i, n) { cin >> ank[i]; }

  vi col(m);
  rep(i, m) {
    cin >> col[i];
    col[i]--;
  }

  int lo = 0;
  int hi = m;

  while (lo < hi) {
    int mi = lo + (hi - lo) / 2;

    bool possible = true;
    vi cnt(n);
    rep(i, mi) { cnt[col[i]] += (mi - i) * (mi - i); }
    rep(i, n) { possible &= ank[i] >= cnt[i]; }

    if (!possible) {
      hi = mi;
    } else {
      lo = mi + 1;
    }
  }

  bool possible = true;
  vi cnt(n);
  rep(i, lo) { cnt[col[i]] += (lo - i) * (lo - i); }
  rep(i, n) { possible &= ank[i] >= cnt[i]; }

  if (possible) {
  } else {
    lo--;
  }
  cout << lo << endl;
}
