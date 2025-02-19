#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define bet(l, x, h) ((l) <= (x) && (x) < (h))

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
  vvi parents(n, vi(m));
  vvi fails(n, vi(m));
  int fail = 0;

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

  auto is_par = [&](pi par, pi chd) -> bool {
    for (auto x : {par.first, chd.first}) {
      if (!bet(0, x, n))
        return 0;
    }

    for (auto x : {par.second, chd.second}) {
      if (!bet(0, x, m))
        return 0;
    }

    return quicksand[par.first][par.second] == 0 &&
           grid[par.first][par.second] == grid[chd.first][chd.second] - 1;
  };

  auto calc_quick = [&](int r, int c) {
    if (!(bet(0, r, n) && bet(0, c, m)))
      return;

    quicksand[r][c] = 0;
    for (auto [dr, dc] : dirs) {
      int nr = r + dr;
      int nc = c + dc;

      if (!(bet(0, nr, n) && bet(0, nc, m)))
        continue;

      if (grid[nr][nc] - grid[r][c] >= 2) {
        quicksand[r][c] = 1;
        return;
      }
    }
  };

  auto calc_quicksand = [&]() {
    rep(i, n) rep(j, m) quicksand[i][j] = 0;

    rep(i, n) {
      rep(j, m) {
        calc_quick(i, j);
      }
    }
  };
  calc_quicksand();

  auto calc_par = [&](int r, int c) {
    if (!(bet(0, r, n) && bet(0, c, m)))
      return;

    parents[r][c] = 0;
    for (auto [dr, dc] : dirs) {
      int nr = r + dr;
      int nc = c + dc;

      parents[r][c] += is_par({nr, nc}, {r, c});
    }
  };

  auto calc_pars = [&]() {
    rep(i, n) {
      rep(j, m) {
        calc_par(i, j);
      }
    }
  };
  calc_pars();

  auto calc_fail = [&](int r, int c) {
    if (!(bet(0, r, n) && bet(0, c, m)))
      return;

    fail -= fails[r][c];
    fails[r][c] = 0;

    int d = grid[r][c];
    if (d == 0 || d == INF)
      return;

    bool is_fail = 1;
    for (auto [dr, dc] : dirs) {
      int nr = r + dr;
      int nc = c + dc;

      is_fail &= !is_par({nr, nc}, {r, c});
    }
    fail += is_fail;
    fails[r][c] = is_fail;
  };

  auto calc_fails = [&]() {
    rep(i, n) {
      rep(j, m) {
        calc_fail(i, j);
      }
    }
  };
  calc_fails();

  auto query = [&](int r, int c) -> string {
    if (fail > 0)
      return "fel";

    if (quicksand[r][c])
      return "ja";

    for (auto [dr, dc] : dirs) {
      int nr = r + dr;
      int nc = c + dc;
      if (is_par({r, c}, {nr, nc}) && parents[nr][nc] <= 1)
        return "nej";
    }

    return "kanske";
  };

  auto upd = [&](int r, int c, int d) -> void {
    if (grid[r][c] == 0)
      fail += 4e5;
    grid[r][c] = d;

    repp(nr, max(r - 2, 0), min(r + 3, n)) {
      repp(nc, max(c - 2, 0), min(c + 3, m)) {
        calc_quick(nr, nc);
      }
    }

    repp(nr, max(r - 2, 0), min(r + 3, n)) {
      repp(nc, max(c - 2, 0), min(c + 3, m)) {
        calc_par(nr, nc);
      }
    }
    repp(nr, max(r - 2, 0), min(r + 3, n)) {
      repp(nc, max(c - 2, 0), min(c + 3, m)) {
        calc_fail(nr, nc);
      }
    }
  };

  rep(_, q) {
    char op;
    cin >> op;
    if (op == '?') {
      int r, c;
      cin >> r >> c;
      r--, c--;

      cout << query(r, c) << '\n';
    } else {
      int r, c, d;
      cin >> r >> c >> d;
      r--, c--;

      if (d == -1)
        d = INF;

      upd(r, c, d);
    }
  }
}
