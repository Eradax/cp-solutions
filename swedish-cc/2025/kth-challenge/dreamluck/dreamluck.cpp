#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
  #define LVLS 19
#else
  #define dbg(...)
  #define LVLS 19
#endif

using namespace std;

#define sz(c) ((int)c.size())

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

  auto check = [&](double delta) -> bool {
    for (auto& v : a) {
      vector<pair<int, double>> smol;
      vector<pair<int, double>> pref;
      smol.emplace_back(-1, INF);
      pref.emplace_back(-1, 0);

      for (auto i : v) {
        smol.emplace_back(i - 1, min(smol.back().second, pref.back().second - delta * i));
        pref.emplace_back(i, pref.back().second + 1);
      }

      int cnt = 0;
      int si = 0, pi = 0;
      for (auto i : v) {
        cnt++;
        while (si + 1 < sz(smol) && i - smol[si + 1].first >= k) si++;
        while (pi + 1 < sz(pref) && i - pref[pi + 1].first >= k) pi++;

        int pp = pref[pi].second;

        if (cnt - pp >= delta * k) {
          dbg("len = ", k);
          return 1;
        }

        if (cnt - delta * (i + 1) > smol[si].second) {
          dbg("len = ", i - smol[si].first);
          return 1;
        }
      }

    }

    return 0;
  };

  double lo = 0;
  double hi = 1;
  for (int _ = 0; _ < LVLS; _++) {
    double mi = (lo + hi) / 2;

    if (!check(mi))
      hi = mi;
    else
      lo = mi;
  }

  cout << fixed << setprecision(9) << (lo + hi) / 2 << endl;
}
