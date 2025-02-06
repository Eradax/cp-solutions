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
#define all(c) c.begin(), c.end()

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vi t(n);
  rep(i, n) {
    cin >> t[i];
  }

  sort(all(t));

  dbg(t);

  vi p(n);
  rep(i, n) {
    p[i] = t[i];
    if (i)
      p[i] += p[i - 1];
  }

  dbg(p);

  int ans = INF;

  rep(i, n) {
    dbg("-----");
    int tmp = 0;
    tmp += t[i] * (i + 1) - p[i];

    dbg(tmp);

    tmp += t[n - 1] * (n - 1 - i) - (p[n - 1] - p[i]);

    dbg(tmp);

    dbg(i, tmp);

    ans = min(ans, tmp);
  }

  cout << ans << endl;
}
