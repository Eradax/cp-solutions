#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    Programmeringsolympiadens final 2019
links:
    https://open.kattis.com/problems/manresor
*/

using namespace std;

static constexpr int INF = 1e9;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)

#define all(c) (c.begin()), (c.end())
#define setcontains(c, i) (c.find(i) != c.end())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, k;
  cin >> n >> m >> k;

  vi d(n), g(m), p(m), r(k);
  rep(i, n) {
    cin >> d[i];
    d[i]--;
  }
  rep(i, m) {
    cin >> g[i];
  }
  rep(i, m) cin >> p[i];
  rep(i, k) {
    cin >> r[i];
    r[i]--;
  }

  sort(all(d));
  sort(all(r));

  dbg(d, g, p, r);

  int l = *max_element(all(d));
  dbg(l);

  vi nxt(l + 1, -2);
  {
    int num = 0;
    rep(i, l + 1) {
      while (num < n && d[num] < i)
        num++;

      // Technically not needed but makes it easier to understand.
      nxt[i] = num >= n ? -1 : num;
    }
  }
  dbg(nxt);

  vi half(n, -2);
  {
    int num = k - 1;
    per(i, n) {
      while (num >= 0 && r[num] > d[i])
        num--;

      // Technically not needed but makes it easier to understand.
      half[i] = num < 0 ? -1 : r[num];
    }
  }
  dbg(half);

  vi dp(n, INF);

  per(i, n) {
    dbg(i);

    int cost = dp[i];

    rep(j, m) {
      int nd = d[i] + g[j];
      int next = nd <= l ? nxt[nd] : -3;
      cost = min(cost, p[j] + (next >= 0 ? dp[next] : 0));

      dbg(i, j, g[j], nd, next, cost);
    }

    rep(j, m) {
      int nd = half[i] + g[j];
      if (half[i] < 0 || nd <= d[i]) { dbg("cont", nd); continue; };
      int next = nd <= l ? nxt[nd] : -3;
      cost = min(cost, p[j] / 2 + (next >= 0 ? dp[next] : 0));

      dbg(j, nd, next, cost);
    }

    dp[i] = cost;
  }

  dbg(dp);

  cout << dp[0] << endl;
}
