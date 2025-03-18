#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;
using ll = long long;

static const ll INF = 1e18;

struct T {
  vector<ll> t;
  vector<ll> la;
  vector<ll> ma, ma2, mac;

  T(int n)
      : t(4 * n),
        la(4 * n),
        ma(4 * n),
        ma2(4 * n),
        mac(4 * n) {}

  void build(int x, int l, int r, vector<ll>& a) {
    la[x] = 0;
    if (l == r) {
      t[x] = ma[x] = a[l];
      mac[x] = 1;
      ma2[x] = -INF;
      return;
    }

    int mid = (l + r) / 2;
    build(2 * x, l, mid, a);
    build(2 * x + 1, mid + 1, r, a);
    combine(x);
  }

  void combine(int x) {
    t[x] = t[2 * x] + t[2 * x + 1];

    if (ma[2 * x] == ma[2 * x + 1]) {
      ma[x] = ma[2 * x];
      ma2[x] = max(ma2[2 * x], ma2[2 * x + 1]);
      mac[x] = mac[2 * x] + mac[2 * x + 1];
    } else if (ma[2 * x] > ma[2 * x + 1]) {
      ma[x] = ma[2 * x];
      ma2[x] = max(ma2[2 * x], ma[2 * x + 1]);
      mac[x] = mac[2 * x];
    } else {
      ma[x] = ma[2 * x + 1];
      ma2[x] = max(ma[2 * x], ma2[2 * x + 1]);
      mac[x] = mac[2 * x + 1];
    }
  }

  void push(int x, int l, int r) {
    int mid = (l + r) / 2;
    put_add(2 * x, l, mid, la[x]);
    put_add(2 * x + 1, mid + 1, r, la[x]);
    la[x] = 0;

    put_ma(2 * x, ma[x]);
    put_ma(2 * x + 1, ma[x]);
  }

  void put_add(int x, int l, int r, ll v) {
    t[x] += (ll)(r - l + 1) * v;
    la[x] += v;

    ma[x] += v;
    if (ma2[x] != -INF)
      ma2[x] += v;
  }

  void put_ma(int x, ll v) {
    if (v >= ma[x])
      return;
    t[x] -= (ll)ma[x] * mac[x];
    ma[x] = v;
    t[x] += (ll)ma[x] * mac[x];
  }

  void chmin(int x, int l, int r, int ql, int qr, ll v) {
    if (l > qr || r < ql || ma[x] <= v)
      return;
    if (l >= ql && r <= qr && v > ma2[x]) {
      put_ma(x, v);
      return;
    }

    push(x, l, r);
    int mid = (l + r) / 2;
    chmin(2 * x, l, mid, ql, qr, v);
    chmin(2 * x + 1, mid + 1, r, ql, qr, v);
    combine(x);
  }

  void add(int x, int l, int r, int ql, int qr, ll v) {
    if (l > qr || r < ql)
      return;
    if (l >= ql && r <= qr) {
      put_add(x, l, r, v);
      return;
    }

    push(x, l, r);
    int mid = (l + r) / 2;
    add(2 * x, l, mid, ql, qr, v);
    add(2 * x + 1, mid + 1, r, ql, qr, v);
    combine(x);
  }

  ll query(int x, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return t[x];

    push(x, l, r);

    int mid = (l + r) / 2;
    return query(2 * x, l, mid, ql, qr) + query(2 * x + 1, mid + 1, r, ql, qr);
  }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, q;
  cin >> n >> q;

  dbg(n, q);

  vector<ll> a(n);
  for (int i = 0; i < n; i++)
    cin >> a[i];

  dbg(a);

  T t(n);
  t.build(1, 0, n - 1, a);
  while (q--) {
    int op, x, y;
    ll z;
    cin >> op >> x >> y;

    dbg(op, x, y);

    if (op == 1) {
      cin >> z;
      t.chmin(1, 0, n - 1, x, y, z);
    } else if (op == 2) {
      cin >> z;
      t.add(1, 0, n - 1, x, y, z);
    } else {
      cout << t.query(1, 0, n - 1, x, y) << '\n';
    }
  }
}
