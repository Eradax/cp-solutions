// WARN: (2025-05-24) This code doesn't work :((
#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
  #define LVLS 5
#else
  #define dbg(...)
  #define LVLS 19
#endif

using namespace std;
using ll = long long;
using pi = pair<int, int>;

#define sz(c) ((int)c.size())
#define slope(x1, y1, x2, y2) ((double)(y1) - (y2)) / ((double)(x1) - (x2))
bool slopecomp(ll x1, ll y1, ll x2, ll y2, ll x3, ll y3, ll x4, ll y4) { return (((y1) - (y2)) * ((x3) - (x4)) >= ((y3) - (y4)) * ((x1) - (x2))); }

const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k;
  cin >> n >> k;

  unordered_map<int, int> comp;
  vector<vector<int>> a(n);
  for (int i = 0; i < n; i++) {
    int v;
    cin >> v;
    v++;

    if (comp[v] == 0)
      comp[v] = comp.size();
    v = comp[v] - 1;

    a[v].push_back(i);
  }

  double ans = 0;

  dbg(a);

  auto cross = [](pi o, pi a, pi b) {
    return (ll)(a.first - o.first) * (b.second - o.second) - (ll)(a.second - o.second) * (b.first - o.first);
  };

  for (auto& v : a) {
    {
      int tmpans = 0;
      int lo = 0;
      for (int hi = 0; hi < sz(v); hi++) {
        while (v[hi] - v[lo] + 1 > k) {
          lo++;
        }

        tmpans = max(tmpans, hi - lo + 1);
      }
      ans = max(ans, (double)tmpans / k);
    }

    if (sz(v) <= 1)
      continue;
    
    vector<int> h;
    int lp = 0, hp = 0;
    tuple<int, int, double> best{-1, -1, -INF}; // lp, rp, slope
    
    for (int rp = 0; rp < sz(v); rp++) {
      while (lp < rp && v[rp] - v[lp] + 1>= k) {
        while (sz(h) >= 2) {
          int p2 = h[sz(h) - 1];
          int p1 = h[sz(h) - 2];

          if (cross({v[p1] - 1, p1}, {v[p2] - 1, p2}, {v[lp] - 1, lp}))
            h.pop_back();
          else
            break;
        }
        
        h.push_back(lp);
        lp++;
      }

      while (hp + 1 < sz(h) && slope(v[h[hp]] - 1, h[hp], v[rp], rp + 1) <= slope(v[h[hp + 1]] - 1, h[hp + 1], v[rp], rp + 1)) hp++;

      if (sz(h)) {
        double cs = slope(v[h[hp]] - 1, h[hp], v[rp], rp + 1);
        if (cs > get<2>(best))
          best = {h[hp], rp, cs};
      }
    }

    ans = max(ans, get<2>(best));
  }
  

  cout << fixed << setprecision(18) << ans << endl;
}
