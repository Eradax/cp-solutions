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

  vvpi ex(n);

  rep(i, m) {
    int ri, ki;
    cin >> ri >> ki;

    vpi vals(ki);
    rep(i, ki) { cin >> vals[i].first >> vals[i].second; }
  }
}
