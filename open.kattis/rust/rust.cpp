#include <bits/stdc++.h>

#ifdef DBG
#include "../../dbg.h"
#else
#define dbg(...)
#endif

/*
source:
    Forritunarkeppni Framhaldsskólanna 2020
links:
    https://open.kattis.com/problems/rust
*/

using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())

inline int acc(vvi *v, int a, int b) {
  if (a < 0 || a >= v->size() || b < 0 || b >= v->at(0).size()) {
    return 0;
  }
  return v->at(a).at(b);
}

inline int block(vvi *v, int a, int b, int l, int r) {
  if (a > l || b > r)
    return 0;

  return acc(v, l, r) - acc(v, l, b - 1) - acc(v, a - 1, r) +
         acc(v, a - 1, b - 1);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, k;
  cin >> n >> k;

  vvi r(n, vi(n)), g(n, vi(n));

  rep(i, n) {
    string line;
    cin >> line;

    int rr = 0, gg = 0;

    rep(j, n) {
      if (line[j] == '.') {
        r[i][j] = rr + acc(&r, i - 1, j);
        g[i][j] = gg + acc(&g, i - 1, j);
      } else if (line[j] == '#') {
        rr += 1;
        r[i][j] = rr + acc(&r, i - 1, j);
        g[i][j] = gg + acc(&g, i - 1, j);
      } else {
        gg += line[j] - '0';
        r[i][j] = rr + acc(&r, i - 1, j);
        g[i][j] = gg + acc(&g, i - 1, j);
      }
    }
  }

  dbg(r, g);

  int ans = 0;
  rep(i, n - k + 1) {
    rep(j, n - k + 1) {
      int perim = 0;
      perim += block(&r, i, j, i + k - 1, j + k - 1) +
               block(&g, i, j, i + k - 1, j + k - 1) -
               block(&r, i + 1, j + 1, i + k - 2, j + k - 2) -
               block(&g, i + 1, j + 1, i + k - 2, j + k - 2);
      dbg(i, j, perim);

      if (perim != 0)
        continue;

      int curr = block(&g, i, j, i + k - 1, j + k - 1);
      ans = max(ans, curr);
    }
  }

  cout << ans << endl;
}
