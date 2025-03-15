#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < n; i++)

using pi = pair<int, int>;
using vi = vector<int>;

using vpi = vector<pi>;

#define sz(c) ((int)c.size())
#define rall(c) c.rbegin(), c.rend()

#define fi first
#define se second

struct RUF {
  vi e;
  vpi st;

  RUF(int n) : e(n, -1) {}
  int size(int x) { return -e[find(x)]; }
  int find(int x) { return e[x] < 0 ? x : find(e[x]); }
  int time() { return sz(st); }
  bool sameSet(int u, int v) { return find(u) == find(v); }

  void undo(int t) {
    for (int i = time()-1; i >= t; i--) {
      e[st[i].fi] = st[i].se;
    }
    st.resize(t);
  }

  bool join(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b)
      return 0;
    if (e[a] > e[b])
      swap(a, b);
    st.emplace_back(a, e[a]);
    st.emplace_back(b, e[b]);
    e[a] += e[b];
    e[b] = a;
    return 1;
  }
};

struct T {
  int n;
  vpi val;

  pi merge(pi a, pi b) {
    dbg(a, b);
    return pi(b.fi + (b.se & 1 ? -1 : 1) * a.fi, b.se + a.se);
  }

  T(int n) : n(n), val(2 * n, pi(0, 0)) {}

  void build() {
    for (int i = n - 1; i >= 1; i--) {
      val[i] = merge(val[2 * i], val[2 * i + 1]);
    }

    dbg(n, val);
  }

  void flip(int x) {
    x += n;

    if (val[x].se & 1) {
      val[x].se = 0;
      val[x].fi = 0;
    } else {
      val[x].se = 1;
      val[x].fi = x - n;
    }

    for (; x > 1; x /= 2) {
      if (x & 1) {
        val[x / 2] = merge(val[x ^ 1], val[x]);
      } else {
        val[x / 2] = merge(val[x], val[x ^ 1]);
      }
    }

    dbg(val);
  }

  pi query(int l, int r) {
    dbg(l, r);
    l += n, r += n;
    pi lr, rr;
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1) {
        dbg(val[l], l);
        lr = merge(lr, val[l++]);
      }
      if (r & 1) {
        rr = merge(val[--r], rr);
        dbg(val[r], r);
      }
    }

    return merge(lr, rr);
  }
};

struct DS {
  int n;
  vi times;
  RUF ruf;
  T t;

  DS(int n) : n(n), ruf(n + 1), t(n + 1) {
    if (n & 1)
      t.val[1 + n] = pi(1, 1);
    t.build();
  }

  void add(int u, int v) {
    times.push_back(ruf.time());

    if (!ruf.sameSet(u, v)) {
      t.flip(ruf.size(u));
      t.flip(ruf.size(v));
      ruf.join(u, v);
      t.flip(ruf.size(u));
    } else {
      ruf.join(u, v);
    }
  }

  void rem() {
    int curr_time = ruf.time();
    int time = times.back();
    times.pop_back();

    dbg(curr_time, time);

    if (time < curr_time) {
      pi a, b;
      b = ruf.st[sz(ruf.st) - 1];
      a = ruf.st[sz(ruf.st) - 2];

      dbg(a, b);

      assert(ruf.sameSet(a.fi, b.fi));
      t.flip(ruf.size(a.fi));
      ruf.undo(time);
      t.flip(ruf.size(a.fi));
      t.flip(ruf.size(b.fi));
    } else {
      ruf.undo(time);  // this does nothing
    }
  }

  int calc() {
    pi res = t.query(0, n + 1);

    return res.fi;
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  DS ds(n);

  dbg(n, q);

  rep(_, q) {
    char op;
    cin >> op;
    if (op == 'a') {
      int u, v, p;
      cin >> u >> v >> p;
      u--;
      v--;

      ds.add(u, v);
    } else if (op == 'r') {
      ds.rem();
    } else {
      int ans = ds.calc();
      cout << ans << endl;
    }
  }
}
