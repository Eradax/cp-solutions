#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

#define int long long

using namespace std;

struct T {
  int n, h;
  vector<int> sum, cnt, lazy;

  T(int n) : n(n), h(__bit_width(n)), sum(2 * n), cnt(2 * n), lazy(n) {}

  void build(int x) {
    while (x > 1) {
      x /= 2;

      dbg(x);

      cnt[x] = cnt[2 * x] + cnt[2 * x + 1];
      sum[x] = sum[2 * x] + sum[2 * x + 1] + cnt[x] * lazy[x];
    }
  }

  void apply(int x, int v) {
    sum[x] += cnt[x] * v;
    if (x < n)
      lazy[x] += v;
  }

  void push(int x) {
    for (int s = h; s >= 1; s--) {
      int i = x >> s;

      if (lazy[i] != 0) {
        apply(2 * i, lazy[i]);
        apply(2 * i + 1, lazy[i]);
        lazy[i] = 0;
      }
    }
  }

  void add(int l, int r, int v) {
    l += n, r += n;

    int l0 = l;
    int r0 = r;

    for (; l < r; l /= 2, r /= 2) {
      if (l & 1)
        apply(l++, v);
      if (r & 1)
        apply(--r, v);
    }

    build(l0);
    build(r0 - 1);
  }

  void flip(int x) {
    x += n;
    push(x);

    dbg(x, cnt[x]);

    assert(cnt[x] <= 1);
    cnt[x] = 1 - cnt[x];

    build(x);

    dbg(x, cnt[x]);

    dbg(cnt);
  }

  int query(int x) {
    x += n;
    push(x);

    return sum[x];
  }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  T t(n);

  while (q--) {
    int op;
    cin >> op;

    if (op == 1) {
      int i;
      cin >> i;
      cout << t.query(i) << '\n';
    } else if (op == 2) {
      int l, r, v;
      cin >> l >> r >> v;
      r++;

      t.add(l, r, v);
    } else if (op == 3) {
      int i;
      cin >> i;
      t.flip(i);
    }
  }

  for (int i = 1; i < n; i++) {
    t.apply(2 * i, t.lazy[i]);
    t.apply(2 * i + 1, t.lazy[i]);
    t.lazy[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    cout << t.sum[i + n] << " \n"[i == n-1];
  }
}
