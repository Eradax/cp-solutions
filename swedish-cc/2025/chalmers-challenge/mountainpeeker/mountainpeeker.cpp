#include <bits/stdc++.h>
#include <limits>

using namespace std;

using ll = long long;
#define int ll

using ld = long double;

using vi = vector<int>;
using vd = vector<ld>;

using pi = pair<int, int>;

using vpi = vector<pi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  int h;
  cin >> h;

  vpi pos, neg;

  rep(i, n) {
    int x, y;
    cin >> x >> y;

    if (x < 0) {
      neg.emplace_back(-x, y);
    } else {
      pos.emplace_back(x, y);
    }
  }

  sort(all(pos));
  sort(all(neg));

  int ans = 0;

  {
    ld ma = -numeric_limits<ld>::infinity();
    for (auto [x, y] : pos) {
      ld nm = (y - h);
      nm /= x;

      if (nm > ma) {
        ma = nm;
        ans++;
      }
    }
  }


  {
    ld ma = -numeric_limits<ld>::infinity();
    for (auto [x, y] : neg) {
      ld nm = (y - h);
      nm /= x;

      if (nm > ma) {
        ma = nm;
        ans++;
      }
    }
  }

  cout << ans << endl;
}
