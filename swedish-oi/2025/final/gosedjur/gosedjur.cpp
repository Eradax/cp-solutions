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

vpi dirs = {
                       {0, 1},
                       {0, -1},
                       {1, 0},
                       {-1, 0}
};

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define setcontains(c, x) (c.find(x) != c.end())

int n, r, c;

vvi grid;
vi ans;

bool bfs(int t, int i, int j) {
  if (grid[i][j] < 0) {
    return false;
  }

  int elem = grid[i][j];

  vi pos(c);

  queue<pi> q;
  vvi seen(r, vi(c, 0));
  q.emplace(i, j);
  seen[i][j] = 1;

  while (!q.empty()) {
    auto [y, x] = q.front();
    q.pop();

    for (auto [dx, dy] : dirs) {
      int nx = x + dx, ny = y + dy;

      if (!(0 <= nx && nx <= c && 0 <= ny && ny <= r)) {
        continue;
      }

      if (grid[ny][nx] != elem) {
        continue;
      }

      if (seen[ny][nx]) {
        continue;
      }

      seen[ny][nx] = 1;
      pos[nx] = max(pos[nx], ny);

      q.emplace(ny, nx);
    }
  }

  bool flag = true;

  rep(a, c) {
    int s = pos[i];

    per(b, s) {
      int c = grid[b][s];
      if (c == elem || ans[c] != -1) {
        flag &= true;
      } else {
        flag = false;
      }
    }
  }

  ans[elem] = t;

  return flag;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  cin >> n >> r >> c;

  grid.resize(r, vi(c, -1));
  ans.resize(n, -1);

  rep(i, r) {
    rep(j, c) {
      cin >> grid[i][j];
      grid[i][j]--;
    }
  }

  // int m = 0;
  // int p = -1;
  // rep(i, r) {
  //   if (grid[i][0] != p) {
  //     ans[grid[i][0]] = m;
  //     m++;
  //     p = grid[i][0];
  //   }
  // }
  
  int time = 0;
  
  rep(i, r) {
    bool flag;
    rep(j, c) {
       
    }
  }

  rep(i, n) { cout << ans[i] << ' '; }
  cout << endl;
}
