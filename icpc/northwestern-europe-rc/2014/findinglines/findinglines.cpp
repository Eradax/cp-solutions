#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
links:
    https://open.kattis.com/problems/findinglines
source:
    Northwestern Europe Regional Contest (NWERC) 2014
*/

using namespace std;

using ld = long double;

#define rep(i, n) for (int i = 0; i < n; i++)

random_device rd;
mt19937 rng(rd());

template <typename T>
inline T randel(vector<T>& v) {
  return v[uniform_int_distribution<int>(int(0), int(v.size()) - int(1))(rng)];
}

struct PH {
  size_t operator()(const pair<ld, ld>& p) const {
    auto h1 = hash<ld>{}(p.first);
    auto h2 = hash<ld>{}(p.second);

    return h1 ^ (h2 << 1);
  }
};

const int INF = INT_MAX;

const int CHECKS = 20;
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, p;
  cin >> n >> p;

  vector<pair<int, int>> c(n);

  rep(i, n) {
    cin >> c[i].first >> c[i].second;
  }

  if (n == 1) {
    cout << "possible" << endl;
    return 0;
  }

  dbg(c);

  rep(check, CHECKS) {
    dbg(check);

    unordered_map<pair<ld, ld>, int, PH> counts;

    auto [x1, y1] = randel(c);

    rep(i, n) {
      dbg(i);

      auto [x2, y2] = c[i];
      if (x1 == x2 && y1 == y2)
        continue;

      ld m, b;

      if (x1 == x2) {
        m = (ld)INF;
        b = x1;
      } else {
        m = ld(y2 - y1) / ld(x2 - x1);
        b = ld(y1 - m * x1);

        if (m * x1 + b != y1) {
          dbg(m * x1 + b, y1);
        }

        if (m * x2 + b != y2) {
          dbg(m * x2 + b, y2);
        }
      }

      counts[{m, b}] += 1;
    }

    for (auto& i : counts) {
      dbg(i.second);

      if (i.second + 1 < (n * p + 100 - 1) / 100)
        continue;

      cout << "possible" << endl;
      return 0;
    }
  }

  cout << "impossible" << endl;
}
