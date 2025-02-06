#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using pi = pair<int, int>;

using vpi = vector<pi>;
using vvpi = vector<vpi>;

using vi = vector<int>;
using vvi = vector<vi>;

using vui = vector<unordered_set<int>>;

using vb = vector<bool>;

static constexpr int INF = 1e9;

vpi dirs = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define perr(i, s, n) for (int i = n - 1; i >= s; i--)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define sz(c) ((int)c.size())
#define setcontains(c, x) (c.find(x) != c.end())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, r, c;
  cin >> n >> r >> c;

  dbg(n, r, c);

  vvi grid(r, vi(c, -1));
  vi ans(n, -1);

  rep(i, r) {
    rep(j, c) {
      cin >> grid[i][j];
      grid[i][j]--;
    }
  }

  vui adj(n);
  vpi lm(n, {INF, -1}), rm(n, {-1, -1});
  vi lp(n, -1), rp(n, -1);
  vvi col_pref(c, vi(r, 0));
  vvi height(r, vi(c, -1));

  {
    vvi placings(r, vi(c, 0));
    vb seen(n);

    rep(rr, r) {
      rep(cc, c) {
        int g = grid[rr][cc];

        if (!seen[g]) {
          seen[g] = 1;
          placings[rr][cc] = 1;
        }

        dbg(cc, lm[g].first, g);

        if (cc < lm[g].first) {
          dbg("lm");
          lm[g] = {cc, rr};
        }

        if (cc > rm[g].first) {
          dbg("rm");
          rm[g] = {cc, rr};
        }
      }
    }

    // rep(cc, c) {
    //   vi gi(n, -1);
    //   rep(rr, r) {
    //     int g = grid[rr][cc];
    //
    //     if (gi[g] == -1) {
    //       gi[g] = rr;
    //     }
    //
    //     height[rr][cc] = gi[g];
    //   }
    // }

    rep(cc, c) {
      rep(rr, r) {
        int g = grid[rr][cc];

        col_pref[cc][rr] = placings[rr][cc];
        if (rr)
          col_pref[cc][rr] += col_pref[cc][rr - 1];
      }
    }

    repp(rr, 1, r) {
      rep(cc, c) {
        int g = grid[rr][cc];
        int ng = grid[rr - 1][cc];

        if (g != ng) {
          adj[g].insert(ng);
        }
      }
    }

    repp(rr, 1, r) {
      rep(cc, c) {
        int g = grid[rr][cc];
        pi l = lm[g], r = rm[g];

        if (l.second > 0) {
          lp[g] = grid[l.second - 1][l.first];
        }

        if (r.second > 0) {
          rp[g] = grid[r.second - 1][r.first];
        }
      }
    }

    dbg(placings, col_pref);

    dbg(lm, rm);
    dbg(lp, rp);
  }

  dbg(adj);

  vi cyc(n);
  vi topo;

  {
    vi col(n);

    function<bool(int)> dfs;
    dfs = [&](int u) {
      dbg(u);

      if (col[u] == 1) {
        return cyc[u] = 1;
      }

      if (col[u] == 2) {
        return cyc[u];
      }

      col[u] = 1;

      bool f = 0;
      for (auto v : adj[u]) {
        f |= dfs(v);
      }

      col[u] = 2;

      if (!f)
        topo.push_back(u);

      return cyc[u] = f;
    };

    rep(i, n) {
      dfs(i);
    }
  }

  vi L(n), U(n), R(n);
  for (auto u : topo) {
    dbg(u);

    int clp = lp[u];

    dbg(clp);

    if (clp != -1) {
      L[u] = L[clp];

      int y = lm[clp].second;
      repp(i, lm[clp].first, lm[u].first) {
        while (y > 0 && grid[y - 1][i] == clp) {
          y--;
        }
        if (grid[y][i] != clp)
          y++;

        // L[u] += col_pref[i][height[y][i]];
        L[u] += col_pref[i][y];

        if (i + 1 != lm[u].first) {
          while (grid[y][i + 1] != clp) {
            y++;
          }
        }
      }
    }

    int crp = rp[u];
    if (crp != -1) {
      R[u] = R[crp];

      int y = rm[crp].second;
      perr(i, rm[u].first + 1, rm[crp].first + 1) {
        while (y > 0 && grid[y - 1][i] == crp) {
          y--;
        }
        if (grid[y][i] != crp)
          y++;

        // assert(grid[y][i] == crp);

        // R[u] += col_pref[i][height[y][i]];
        R[u] += col_pref[i][y];

        if (i - 1 != rm[u].first) {
          while (grid[y][i - 1] != crp) {
            y++;
          }

          assert(grid[y][i - 1] == crp);
        }
      }
    }

    int y = lm[u].second;
    repp(i, lm[u].first, rm[u].first + 1) {
      while (y > 0 && grid[y][i] == u)
        y--;
      if (grid[y][i] != u)
        y++;

      // int h = height[y][i] - 1;
      int h = y - 1;

      if (i + 1 != rm[u].first + 1) {
        while (grid[y][i + 1] != u)
          y++;
      }

      if (h >= 0) {
        U[u] += col_pref[i][h];
      }
    }

    ans[u] = L[u] + U[u] + R[u];
  }

  rep(i, n) {
    cout << ans[i] << ' ';
  }
  cout << endl;
}
