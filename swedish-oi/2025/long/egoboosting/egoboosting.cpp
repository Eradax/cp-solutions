#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

static const int INF = 1e9 + 100;

using vi = vector<int>;

struct UF {
  vi e;
  vi lm, rm;

  UF(int n) : e(n, -1), lm(n, INF), rm(n, -1) {
    for (int i = 0; i < n; i++) {
      lm[i] = rm[i] = i;
    }
  }
  int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
  bool sameset(int a, int b) { return find(a) == find(b); }
  int getLeft(int x) { return lm[find(x)]; }
  int getRight(int x) { return rm[find(x)]; }
  bool join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return 0;

    if (e[a] > e[b])
      swap(a, b);

    e[a] += e[b];
    e[b] = a;

    lm[a] = min(lm[a], lm[b]);
    rm[a] = max(rm[a], rm[b]);

    return 1;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, e;
  cin >> n >> e;

  vector<int> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  auto check = [&](int e) -> bool {
    UF uf(n);

    int l, r = -1;

    while (1) {
      int i = r + 1;

      for (; i < n; i++) {
        if (a[i] <= e)
          break;
      }

      if (i == n)
        break;

      l = i;
      r = i;

      dbg(e, l, r);

      while (1) {
        if (l > 0 && e + r - l + 1 >= a[l - 1]) {
          uf.join(l - 1, l);
          l = uf.getLeft(l);
          r = uf.getRight(r);
        } else if (r < n-1 && e + r - l + 1 >= a[r + 1]) {
          uf.join(r, r+1);
          l = uf.getLeft(l);
          r = uf.getRight(r);
        } else if (r < n-1 && e + r - l + 1 >= a[r + 1]) {
        } else {
          break;
        }
      }
    }

    dbg(e, l, r);

    return l == 0 && r == n-1;
  };

  int lo = 0;
  int hi = INF;

  while (lo < hi) {
    int mi = lo + (hi - lo) / 2;

    if (check(mi)) {
      hi = mi;
    } else {
      lo = mi + 1;
    }
  }

  cout << max(0, lo - e) << endl;
}
