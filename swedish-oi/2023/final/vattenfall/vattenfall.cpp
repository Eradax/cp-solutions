#include <bits/stdc++.h>
// #include "../../../../dbg.h"
#define dbg(...)

using namespace std;

#define sz(c) ((int)c.size())
#define rep(i, n) for (int i = 0; i < (n); i++)

const bool dbgf = true;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c;
  cin >> r >> c;

  int k, n;
  cin >> k >> n;

  vector<int> water(k);
  rep(i, k) cin >> water[i];

  dbg(water);
  dbg("-------");

  unordered_set<long long> cliffPoints;
  unordered_map<int, vector<int>> cliffs;
  rep(i, n) {
    int a, b;
    cin >> a >> b;

    cliffPoints.insert(((long long)b << 32) + (long long)a);

    cliffs[b].push_back(a);
  }

  dbg("Cliffs before");
  for (auto& [u, v] : cliffs) {
    dbg(u, v);
  }

  for (auto& [key, value] : cliffs) {
    sort(value.begin(), value.end());
  }

  dbg("Cliffs after");
  for (auto& [u, v] : cliffs) {
    dbg(u, v);
  }
  dbg("-------");

  queue<pair<long long, long long>> q;
  rep(i, k) {
    dbg("Added", water[i], c);
    q.emplace(water[i], c);
  }

  unordered_set<long long> vis;

  int res = 0;
  int count = 0;
  while (!q.empty()) {
    count++;

    // if (count > 20) break;

    auto [x, y] = q.front();
    q.pop();

    // dbg(x, y);
    if (abs(x - 11) < 2 || dbgf) {
      dbg(x, y);
      dbg("-------");
    }

    if (vis.find((x << 32) + y) != vis.end())
      continue;
    vis.insert((x << 32) + y);

    if (y <= 0) {
      res++;
      continue;
    }

    if (cliffPoints.find(((x << 32) + y - 1)) != cliffPoints.end()) {
      if (0 <= x - 1 && x - 1 < c &&
          cliffPoints.find((((x - 1) << 32) + y)) == cliffPoints.end()) {
        if (abs(x - 11) < 2 || dbgf) {
          dbg("Added", x - 1, y);
        }
        q.emplace(x - 1, y);
      }

      if (0 <= x + 1 && x + 1 < c &&
          cliffPoints.find((((x + 1) << 32) + y)) == cliffPoints.end()) {
        if (abs(x - 11) < 2 || dbgf) {
          dbg("Added", x + 1, y);
        }
        q.emplace(x + 1, y);
      }
    } else {
      int lo, hi;
      lo = 0;
      hi = sz(cliffs[x]) - 1;

      if (abs(x - 11) < 2 || dbgf) {
        dbg(cliffs[x], x, y);
        dbg("-------");
      }

      while (lo < hi) {
        int mi = (lo + hi + 1) / 2;

        if (cliffs[x][mi] >= y) {
          hi = mi - 1;
        } else {
          lo = mi;
        }
      }

      if (hi >= 0 && cliffs[x][lo] >= y)
        hi = -1;
      if (lo == 0 && hi == 0 && cliffs[x][0] < y)
        lo = 0;

      if (abs(x - 11) < 2 || dbgf) {
        dbg(lo, hi, cliffs[x], x, y);
        dbg("-------");
      }

      if (hi < 0) {
        if (abs(x - 11) < 2 || dbgf)
          dbg("Added", x, 0);
        q.emplace(x, 0);
      } else {
        if (abs(x - 11) < 2 || dbgf)
          dbg("Added", x, lo + 1);
        q.emplace(x, cliffs[x][lo] + 1);
      }
    }
  }

  for (auto& u : vis)
    dbg(u >> 32, (int)u);

  cout << res << endl;
}
