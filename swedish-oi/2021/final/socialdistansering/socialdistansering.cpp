#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()

using ll = long long;

using vi = vector<int>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  ll k;
  cin >> n >> m >> k;

  vector<pair<ll, ll>> tmp(m);
  rep(i, m) { cin >> tmp[i].first >> tmp[i].second; }
  sort(all(tmp));

  ll prev = -1;
  vi v(m + 1);

  ll sum = 0;
  rep(i, m) {
    auto [a, b] = tmp[i];

    v[i] = a - 1 - prev;
    prev = b;

    sum += v[i];
  }
  v[m] = k - 1 - prev;
  sum += v[m];

  dbg(v);

  ll d = sum / n;

  // ll lo = max(d - m, 0LL);
  // ll hi = d + m;

  ll lo = 1, hi = k;

  while (lo < hi) {
    ll mi = lo + (hi - lo) / 2;

    dbg(mi);

    ll prev = -1;
    int cnt = 0;

    rep(i, m + 1) {
      ll start = (i ? tmp[i - 1].second + 1 : 0);
      ll end = (i < m ? tmp[i].first - 1 : k - 1);
      ll rstart = max(start, prev + 1);
      ll len = max(end - rstart + 1, 0LL);

      ll curr = (len + mi - 1) / mi;

      dbg("----------");
      dbg(rstart, start, end, len, prev, curr);

      cnt += curr;
      if (curr)
        prev = rstart + (curr - 1) * mi + mi - 1;
    }

    dbg(cnt);

    if (cnt < n) {
      hi = mi;
    } else {
      lo = mi + 1;
    }
  }

  cout << lo - 1 << endl;
}
