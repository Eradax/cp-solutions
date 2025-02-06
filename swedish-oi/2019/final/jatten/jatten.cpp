#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ld = long double;
using ll = long long;

using pi = pair<int, int>;
vector<pi> dirs = {{-1, 0}, {-1, 1}, {-1, -1}, {1, 0},
                   {1, -1}, {1, 1},  {0, 1},   {0, -1}};

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

ll sqlen(int x1, int y1, int x2, int y2) {
  ll xd = x1 - x2;
  ll yd = y1 - y2;

  return xd * xd + yd * yd;
}

bool valid(int x1, int y1, int x2, int y2, int x3, int y3) {
  ll a2 = sqlen(x1, y1, x2, y2);
  ll b2 = sqlen(x2, y2, x3, y3);
  ll c2 = sqlen(x3, y3, x1, y1);

  vector<ll> sidelengths = {a2, b2, c2};
  sort(all(sidelengths));

  return sidelengths[0] + sidelengths[1] < sidelengths[2];
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  int x1, y1;
  cin >> x1 >> y1;

  int x2, y2;
  cin >> x2 >> y2;

  vector<pi> ends = {{x1, y1}, {x2, y2}};

  for (auto [x3, y3] : ends) {
    int x3s = x3;
    int y3s = y3;
    repp(i, -2, 2) {
      repp(j, -2, 2) {
        x3 = x3s;
        y3 = y3s;
        x3 += i;
        y3 += j;

        if (!((0 <= x3 && x3 < n) && (0 <= y3 && y3 < m))) {
          continue;
        }

        ll efwgr = (ll)x1 * (ll)(y2 - y3) + (ll)x2 * (ll)(y3 - y1) +
                   (ll)x3 * (ll)(y1 - y2);

        if (efwgr == 0) {
          continue;
        }

        if (valid(x1, y1, x2, y2, x3, y3)) {
          cout << x3 << " " << y3 << endl;
          return 0;
        }
      }
    }
  }

  assert(0);
}
