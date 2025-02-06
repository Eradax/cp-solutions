#include <bits/stdc++.h>

using namespace std;

using ll = long long;
#define int ll

using ld = long double;

using vi = vector<int>;
using vd = vector<ld>;

#define rep(i, n) for (int i = 0; i < (n); i++)

vector<vector<char>> orders = {{'R', 'G', 'B'}, {'R', 'B', 'G'},
                               {'G', 'R', 'B'}, {'G', 'B', 'R'},
                               {'B', 'R', 'G'}, {'B', 'G', 'R'}};

struct F {
  int x, y;

  F(int x, int y) : x(x), y(y) {}
};

ld dist(const F &a, const F &b) {
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

ld distOrigin(const F &a) {
  return sqrt(1LL * a.x * a.x + 1LL * a.y * a.y);
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<F> R, G, B;

  for (int i = 0; i < n; i++) {
    int x, y;
    char c;
    cin >> x >> y >> c;
    if (c == 'R')
      R.emplace_back(x, y);
    else if (c == 'G')
      G.emplace_back(x, y);
    else if (c == 'B')
      B.emplace_back(x, y);
  }

  auto gFs = [&](char c) -> vector<F> & {
    if (c == 'R')
      return R;
    if (c == 'G')
      return G;
    return B;
  };

  ld best = numeric_limits<ld>::infinity();

  for (auto order : orders) {
    const vector<F> &first = gFs(order[0]);
    const vector<F> &second = gFs(order[1]);
    const vector<F> &third = gFs(order[2]);

    vd cost1(first.size());
    rep(i, first.size()) { cost1[i] = distOrigin(first[i]); }

    vd cost2(second.size(), numeric_limits<ld>::infinity());
    rep(j, second.size()) {
      rep(i, first.size()) {
        ld cand = cost1[i] + dist(first[i], second[j]);
        if (cand < cost2[j])
          cost2[j] = cand;
      }
    }

    rep(k, third.size()) {
      ld cand = numeric_limits<ld>::infinity();
      rep(j, second.size()) {
        ld cur = cost2[j] + dist(second[j], third[k]);
        if (cur < cand)
          cand = cur;
      }
      cand += distOrigin(third[k]);
      best = min(best, cand);
    }
  }

  cout.precision(15);
  cout << best << "\n";

  return 0;
}
