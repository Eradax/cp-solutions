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

int query(int a) {
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

vi solve(int lo, int hi) {
  vi ans;

  if (lo > hi) {
    return ans;
  }

  int mi = lo + (hi - lo) / 2;

  int res = query(mi);

  if (res == mi) {
    for (auto i : solve(lo, mi - 1)) {
      ans.push_back(i);
    }
    if (lo <= res && res <= hi) ans.push_back(res);
    for (auto i : solve(mi + 1, hi)) {
      ans.push_back(i);
    }
  } else if (res < mi) {
    for (auto i : solve(lo, res - 1)) {
      ans.push_back(i);
    }
    if (lo <= res && res <= hi) ans.push_back(res);
    for (auto i : solve(mi + 1, hi)) {
      ans.push_back(i);
    }
  } else if (res > mi) {
    for (auto i : solve(0, mi - 1)) {
      ans.push_back(i);
    }
    if (lo <= res && res <= hi) ans.push_back(res);
    for (auto i : solve(res + 1, hi)) {
      ans.push_back(i);
    }
  }

  return ans;
}

signed main() {
  int t;
  cin >> t;

  // vi ank = solve(0, 1e9);

  vi ank;

  int f = query(-1);
  int l = query(1e9+1);
  repp(i, f, l+1) {
    ank.push_back(i);
  }

  dbg(ank);

  answer(ank);
}
