#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

#define int long long

using namespace std;

struct T {
  int n;
  vector<int> bit, prev, ans, on;

  T(int n) : n(n + 1), bit(n + 1), prev(n + 1), ans(n + 1), on(n + 1) {}

  void add(int x, int v) {
    x++;
    for (; x < n; x += x & -x) {
      bit[x] += v;
    }
  }

  void add(int l, int r, int v) {
    add(l, v);
    add(r, -v);
  }

  int query_sum(int x) {
    x++;
    int ans = 0;

    for (; x >= 1; x -= x & -x) {
      ans += bit[x];
    }

    return ans;
  }

  void flip(int x) {
    x++;
    on[x] = 1 - on[x];

    if (on[x]) {
      prev[x] = query_sum(x-1);
    } else {
      ans[x] += query_sum(x-1) - prev[x];
    }
  }

  int query(int x) {
    x++;

    int ret = ans[x];
    if (on[x]) {
      ret += query_sum(x-1) - prev[x];
    }

    return ret;
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

  for (int i = 0; i < n; i++) {
    cout << t.query(i) << " \n"[i == n - 1];
  }
}
