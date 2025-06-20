#pragma GCC optimize("O3")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../dbg.h"
  #define LVLS 10
#else
  #define dbg(...)
  #define LVLS 30
#endif

using namespace std;

#define sz(c) ((int)c.size())

const int INF = 1e9;

typedef uint64_t ull;
ull C = 3'964'846'488'687'501'853;
template<class T>
struct HashMap {
  int b;
  int size = 0;
  vector<pair<ull, T>> v;
  HashMap(int b) : b(b), v(1<<b) {}
  T& operator[](ull x) { // x=0 NOT OK. All others ok
    ull y = (x*(ull)C) >> (64 - b), m = (1<<b) - 1;
    while (v[y].first && v[y].first != x) ++y &= m;
    size += v[y].first == 0;
    v[y].first = x;
    return v[y].second;
  }
};
ull hsh(ull a, ull b, ull c) {
  return ((a*C +b)*C +c)*C;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int k;
  cin >> k;

  HashMap<int> comp(20);
  vector<vector<int>> a(1);
  string s;
  cin >> s;
  for (int i = 0; i < sz(s); i++) {
    if (s[i] == '1')
      a[0].push_back(i);
  }

  dbg(a);

  auto check = [&](double delta) -> pair<int, int> {
    for (auto& v : a) {
      vector<pair<int, double>> smol;
      vector<pair<int, double>> pref;
      smol.emplace_back(-1, INF);
      pref.emplace_back(-1, 0);

      for (auto i : v) {
        if (smol.back().second > pref.back().second - delta * i) smol.emplace_back(i - 1, min(smol.back().second, pref.back().second - delta * i));
        pref.emplace_back(i, pref.back().second + 1);
      }

      int cnt = 0;
      int si = 0, pi = 0;
      for (auto i : v) {
        cnt++;
        while (si + 1 < sz(smol) && i - smol[si + 1].first >= k) si++;
        while (pi + 1 < sz(pref) && i - pref[pi + 1].first >= k) pi++;

        int pp = pref[pi].second;

        dbg(smol, si);

        if (i + 1 >= k && cnt - pp >= delta * k)
          return make_pair(i, i - k);

        if (cnt - delta * (i + 1) > smol[si].second)
          return make_pair(i, smol[si].first);
      }

    }

    return make_pair(-1, -1);
  };

  double lo = 0;
  double hi = 1;
  for (int _ = 0; _ < LVLS; _++) {
    double mi = (lo + hi) / 2;

    if (check(mi).first == -1)
      hi = mi;
    else
      lo = mi;
  }

  auto [r, l] = check(lo);

  dbg(lo);
  dbg(l, r);

  if (r == -1)
    cout << 1 << ' ' << k << endl;
  else
    cout << l + 2 << ' ' << r - l << endl;
}
