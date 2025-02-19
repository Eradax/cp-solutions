#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

using pi = pair<int, int>;

using vpi = vector<pi>;
using vvpi = vector<vpi>;

using vi = vector<int>;
using vvi = vector<vi>;

static const vpi dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
static const int INF = 1e9;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, q;
  cin >> n >> m >> q;

  dbg(n, m, q);

  pi start;
  vvi grid(n, vi(m));
  vvi quicksand(n, vi(m));

  rep(i, n) {
    rep(j, m) {
      cin >> grid[i][j];
      if (grid[i][j] == -1)
        grid[i][j] = INF;
      if (grid[i][j] == 0)
        start = {i, j};
    }
  }

  dbg(start, grid);

  auto calc_quicksand = [&]() {
    rep(i, n) rep(j, m) quicksand[i][j] = 0;

    rep(i, n) {
      rep(j, m) {
        for (auto [dr, dc] : dirs) {
          int oi = i, oj = j;
          int ni = i + dr, nj = j + dc;
          dbg(i, j, ni, nj);
          if (!(0 <= ni && ni < n && 0 <= nj && nj < m))
            continue;
          if (grid[oi][oj] > grid[ni][nj])
            swap(oi, ni), swap(oj, nj);

          if (grid[ni][nj] - grid[oi][oj] >= 2) {
            dbg(oi, oj);
            dbg(ni, nj);
            dbg(grid[ni][nj], grid[oi][oj]);
            quicksand[oi][oj] = 1;
          }
        }
      }
    }
  };

  vvi calced_grid(n, vi(m));
  vvi seen(n, vi(m));
  auto calc_grid = [&](pi start) {
    rep(i, n) rep(j, m) calced_grid[i][j] = INF;
    rep(i, n) rep(j, m) seen[i][j] = 0;

    for (auto& i : quicksand)
      dbg(i);

    int dist = 0;
    vpi curr, nxt;
    curr.push_back(start);
    calced_grid[start.first][start.second] = 0;
    seen[start.first][start.second]++;
    while (!curr.empty()) {
      dist++;
      nxt.clear();

      dbg(curr);

      for (auto [r, c] : curr) {
        if (quicksand[r][c])
          continue;
        for (auto [dr, dc] : dirs) {
          int nr = r + dr, nc = c + dc;
          if (!(0 <= nr && nr < n && 0 <= nc && nc < m))
            continue;

          if (seen[nr][nc]) {
            if (calced_grid[nr][nc] == dist)
              seen[nr][nc]++;
            continue;
          }
          seen[nr][nc]++;
          calced_grid[nr][nc] = dist;
          nxt.emplace_back(nr, nc);
        }
      }
      swap(curr, nxt);
    }
  };

  calc_quicksand();
  calc_grid(start);
  bool bad = 0;
  rep(i, n) rep(j, m) bad |= grid[i][j] != calced_grid[i][j];

  auto maybe = [&](int r, int c) -> bool {
    int d = grid[r][c];
    bool ret = 1;
    for (auto [dr, dc] : dirs) {
      int nr = r + dr, nc = c + dc;
      if (!(0 <= nr && nr < n && 0 <= nc && nc < m))
        continue;

      int nd = grid[nr][nc];

      if (nd == d + 1 && seen[nr][nc] <= 1) {
        ret = 0;
      }
    }

    return ret;
  };

  rep(_, q) {
    char op;
    cin >> op;
    if (op == '?') {
      int r, c;
      cin >> r >> c;
      r--, c--;

      if (bad) {
        cout << "fel";
      } else if (quicksand[r][c]) {
        cout << "ja";
      } else if (maybe(r, c)) {
        cout << "kanske";
      } else {
        cout << "nej";
      }
      cout << '\n';
    } else {
      int r, c, d;
      cin >> r >> c >> d;
      r--, c--;

      if (d == -1)
        d = INF;

      grid[r][c] = d;
      calc_quicksand();
      calc_grid(start);
      bad = 0;
      rep(i, n) rep(j, m) bad |= grid[i][j] != calced_grid[i][j];
    }
  }
}
