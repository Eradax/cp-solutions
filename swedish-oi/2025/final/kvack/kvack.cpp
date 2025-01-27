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
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())

int query(int a) {
  dbg(a);
  cout << "? " << a << endl;

  int res;
  cin >> res;

  return res;
}

void answer(vi v) {
  cout << "! " << sz(v) << endl;
  rep(i, sz(v)) { cout << v[i] << " "; }
  cout << endl;

  exit(0);
}

void solve(vi* ans, int f, int l) {
  dbg(f, l);

  if (f > l) {
    return;
  }

  if (f == l) {
    int a = query(f);
    if (a == f) ans->push_back(a);
    return;
  }

  int mi = (l + f + 1) / 2;

  int res = query(mi);

  if (f <= res && res <= l) {
    ans->push_back(res);
  }

  if (res == f) {
    // next query should be over [m + m - f, l]
    solve(ans, max(mi + mi - f, f+1), l);
  }

  else if (res == l) {
    // next query should be over [f, m - (l - m) - 1]

    solve(ans, f, min(mi - (l - mi) - 1, l-1));
  }

  else if (res < mi) {
    // next queries are over [f, res-1] and [m + m - res, l]

    solve(ans, f, res - 1);
    solve(ans, max(mi + mi - res, res+1), l);
  }

  else if (res > mi) {
    // next queries are over [f, m - (m - res) - 1] and [res + 1, l]

    solve(ans, f, min(mi - (res - mi) - 1, res-1));
    solve(ans, res + 1, l);
  }
  else if (res == mi) {
    // nex queries are over [f, m - 1] and [m + 1, l]
    solve(ans, f, mi-1);
    solve(ans, mi+1, l);
  }
}

signed main() {
  int t;
  cin >> t;

  vi ank;

  int f = query(-1);
  int l = query(1e9+1);

  ank.push_back(f);
  ank.push_back(l);

  solve(&ank, f+1, l-1);

  dbg(ank);

  answer(ank);
}
