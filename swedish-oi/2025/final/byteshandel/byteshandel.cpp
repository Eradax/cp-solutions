#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = long long;

#define int ll

using pi = pair<int, int>;

using vpi = vector<pi>;
using vvpi = vector<vpi>;

using vi = vector<int>;
using vvi = vector<vi>;

static constexpr int INF = 1e18;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define setcontains(c, x) (c.find(x) != c.end())

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  assert(n == 3);

  vvpi abtoc;
  int atob = INF, atoc = INF, btoc = INF, btoa = INF;

  rep(i, m) {
    int ri, ki;
    cin >> ri >> ki;

    vpi vals(ki);
    rep(i, ki) { cin >> vals[i].first >> vals[i].second; }

    if (ri == 0) {
      if (ki > 1 || vals[0].second != 1)
        continue;
      btoa = min(btoa, vals[0].first);
    } else if (ri == 1) {
      if (ki > 1 || vals[0].second != 0)
        continue;
      atob = min(atob, vals[0].first);
    } else if (ri == 2) {
      if (ki == 1 && vals[0].second == 0) {
        atoc = min(atoc, vals[0].first);
      } else if (ki == 1 && vals[0].second == 1) {
        btoc = min(btoc, vals[0].first);
      } else if (ki == 2) {
        abtoc.push_back(vals);
      }
    }
  }

  dbg(atob, atoc, btoc, btoa, abtoc);

  int ans = INF;
  if (atoc) ans = min(ans, atoc);

  if (atob < btoa && btoa < INF && atob < INF) {
    ans = min(ans, atob);
  }

  if (atob + btoc < INF) ans = min(ans, atob * btoc);

  for (auto i : abtoc) {
    int cost;
    if (i[0].second == 0) {
      cost = i[0].first;
    }

    if (i[1].second == 0) {
      cost = i[1].first;
    }

    if (i[0].second == 1) {
      cost += i[0].first * atob;
    }

    if (i[1].second == 1) {
      cost += i[1].first * atob;
    }

    ans = min(ans, cost);
  }

  cout << ans << endl;
}
