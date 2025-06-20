#include <bits/stdc++.h>
#ifdef DBG
  #include "/home/eradax/persist/cp/cp-solutions/dbg.h"
#else
  #define dbg(...)
#endif
using namespace std;

using a3 = array<int, 3>;
using v3 = vector<a3>;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

const v3 dirs =
    {{0, 0, 1}, {0, 0, -1}, {0, 1, 0}, {0, -1, 0}, {1, 0, 0}, {-1, 0, 0}};

a3 operator+(a3 l, a3 r) {
  a3 res;
  res[0] = l[0] + r[0];
  res[1] = l[1] + r[1];
  res[2] = l[2] + r[2];

  return res;
}

#define beti(l, v, r) ((l <= v) && (v <= r))

bool bet(a3 a, int l, int r, int c) {
  return beti(0, a[0], l - 1) && beti(0, a[1], r - 1) && beti(0, a[2], c - 1);
}

void solve(int l, int r, int c) {
  vvvi grid(l, vvi(r, vi(c)));

  a3 s, t;

  for (int ll = 0; ll < l; ll++) {
    for (int rr = 0; rr < r; rr++) {
      string line;
      cin >> line;

      for (int cc = 0; cc < c; cc++) {
        if (line[cc] == 'S') {
          s = {ll, rr, cc};
        } else if (line[cc] == 'E') {
          t = {ll, rr, cc};
        } else if (line[cc] == '#') {
          grid[ll][rr][cc] = 1;
        }
      }
    }
  }

  dbg(s, t);

  vvvi vis(l, vvi(r, vi(c)));
  queue<pair<int, a3>> q;

  vis[s[0]][s[1]][s[2]] = 1;
  q.emplace(0, s);
  while (!q.empty()) {
    dbg(q);
    auto [w, cord] = q.front();
    q.pop();

    if (cord == t) {
      cout << "Escaped in " << w << " minute(s)." << '\n';
      return;
    }

    for (auto delta : dirs) {
      a3 ncord = cord + delta;
      if (!bet(ncord, l, r, c))
        continue;
      if (vis[ncord[0]][ncord[1]][ncord[2]])
        continue;
      if (grid[ncord[0]][ncord[1]][ncord[2]])
        continue;
      vis[ncord[0]][ncord[1]][ncord[2]] = 1;
      q.emplace(w + 1, ncord);
    }
  }

  cout << "Trapped!" << '\n';
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int l, r, c;
  while (cin >> l >> r >> c && l) {
    solve(l, r, c);
  }
}
