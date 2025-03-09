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
  vector<int> sum, cnt, lazy, fliped;

  T(int n)
      : n(n), h(__bit_width(n)), sum(2 * n), cnt(2 * n), lazy(n), fliped(n) {}

  void apply_sum(int x, int v, int k) {
    sum[x] += cnt[x] * v;
    if (x < n)
      lazy[x] += v;
  }

  void apply_flip(int x, int k) {
    cnt[x] = k - cnt[x];

    if (x < n)
      fliped[x] ^= 1;
  }

  void calc(int x, int k) {
    cnt[x] = cnt[2 * x] + cnt[2 * x + 1];
    sum[x] = sum[2 * x] + sum[2 * x + 1] + cnt[x] * lazy[x];
  }

  void build(int l, int r) {
    l += n, r += n - 1;
    int k = 1;

    for (; l > 1;) {
      k *= 2, l /= 2, r /= 2;
      for (int i = r; i >= l; i--) {
        calc(i, k);
      }
    }
  }

  void push(int l, int r, int b) {
    l += n, r += n - 1;
    for (int s = h; s >= 1; s--) {
      int ll = l >> s;
      int rr = r >> s;

      int k = 1 << s;

      if (fliped[ll]) {
        apply_flip(2 * ll, k / 2);
        apply_flip(2 * ll + 1, k / 2);
        fliped[ll] = 0;
      }

      if (lazy[ll] != 0) {
        apply_sum(2 * ll, lazy[ll], k / 2);
        apply_sum(2 * ll + 1, lazy[ll], k / 2);
        lazy[ll] = 0;
      }

      if (fliped[rr]) {
        apply_flip(2 * rr, k / 2);
        apply_flip(2 * rr + 1, k / 2);
        fliped[rr] = 0;
      }

      if (lazy[rr] != 0) {
        apply_sum(2 * rr, lazy[rr], k / 2);
        apply_sum(2 * rr + 1, lazy[rr], k / 2);
        lazy[rr] = 0;
      }
    }
  }

  void push(int x) {
    x += n;
    for (int s = h; s >= 1; s--) {
      int i = x >> s;
      int k = 1 << s;

      dbg(i, k);
      assert(!(fliped[i] & (lazy[i] > 0)));
      if (fliped[i]) {
        apply_flip(2 * i, k / 2);
        apply_flip(2 * i + 1, k / 2);
        fliped[i] = 0;
      }

      if (lazy[i] != 0) {
        apply_sum(2 * i, lazy[i], k / 2);
        apply_sum(2 * i + 1, lazy[i], k / 2);
        lazy[i] = 0;
      }
    }
  }

  void push(int l, int r) {
    l += n, r += n - 1;
    int s = h;
    int k = 1 << (h - 1);
    for (; s >= 1; s--, k /= 2) {
      for (int i = l >> s; i <= r >> s; i++) {
        assert(!(fliped[i] & (lazy[i] > 0)));
        if (fliped[i]) {
          apply_flip(2 * i, k);
          apply_flip(2 * i + 1, k);
          fliped[i] = 0;
        }

        if (lazy[i] != 0) {
          apply_sum(2 * i, lazy[i], k);
          apply_sum(2 * i + 1, lazy[i], k);
          lazy[i] = 0;
        }
      }
    }
  }

  void add(int l, int r, int v) {
    push(l, l+1);
    push(r-1, r);

    int l0 = l;
    int r0 = r;

    int k = 1;
    l += n, r += n;
    for (; l < r; l /= 2, r /= 2, k *= 2) {
      if (l & 1)
        apply_sum(l++, v, k);
      if (r & 1)
        apply_sum(--r, v, k);
    }

    build(l0, l0 + 1);
    build(r0 - 1, r0);
  }

  void flip(int l, int r) {
    push(l, l + 1);
    push(r - 1, r);

    int l0 = l;
    int r0 = r;

    int k = 1;
    l += n, r += n;
    for (; l < r; l /= 2, r /= 2, k *= 2) {
      if (l & 1) {
        if (l < n)
          dbg(lazy[l]);
        apply_flip(l++, k);
      }
      if (r & 1) {
        if (r - 1 < n)
          dbg(lazy[r - 1]);
        apply_flip(--r, k);
      }
    }

    build(l0, l0 + 1);
    build(r0 - 1, r0);
  }

  int query(int x) {
    push(x, x + 1);

    return sum[x + n];
  }

  int query(int l, int r) {
    dbg(l, r);
    push(l, r);
    int ans = 0;
    l += n, r += n;
    for (; l < r; l /= 2, r /= 2) {
      dbg(l, r);
      if (l & 1)
        ans += sum[l++];
      if (r & 1)
        ans += sum[--r];
    }

    return ans;
  }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  T t(n);

  while (q--) {
    dbg(t.sum, t.lazy, t.cnt, t.fliped);

    int op;
    cin >> op;

    if (op == 1) {
      int l, r;
      cin >> l >> r;
      cout << t.query(l, r + 1) << '\n';
    } else if (op == 2) {
      int l, r, v;
      cin >> l >> r >> v;

      t.add(l, r + 1, v);
    } else if (op == 3) {
      int l, r;
      cin >> l >> r;
      t.flip(l, r + 1);
    }
  }

  dbg(t.sum, t.lazy, t.cnt, t.fliped);
  t.push(0, n);

  for (int i = 0; i < n; i++) {
    cout << t.sum[i + n] << " \n"[i == n - 1];
  }
}
