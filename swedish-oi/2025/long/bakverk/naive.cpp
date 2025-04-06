#pragma GCC optimize("Ofast")
#include <bits/allocator.h>
#pragma GCC target("avx2")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

int main() {
  int x, y;
  cin >> x >> y;

  if (y > x) {
    cout << -1 << endl;
    return 0;
  }

  assert(x <= 20);
  int n = 30, m = 0;
  vector<pair<int, int>> edg;
  for (int i = 0; i < x; i++) {
    dbg(0, i + 1);
    edg.emplace_back(0, i + 1);
    m++;
  }

  for (int i = 0; i < y; i++) {
    dbg(i + 1, n - 1);
    edg.emplace_back(i + 1, n - 1);
    m++;
  }

  dbg(edg);

  cout << n << " " << m << '\n';
  for (auto [u, v] : edg) {
    cout << u + 1 << " " << v + 1 << '\n';
  }
}
