#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct T {
  vector<ll> t;
  vector<int> m;
  T(int n) : t(4 * n), m(4 * n) {}

  void mod(int x, int l, int r, int ql, int qr, int v) {
    if (l > qr || r < ql || m[x] < v)
      return;
    if (l == r) {
      t[x] %= v;
      m[x] = t[x];
      return;
    }

    int mid = (l + r) / 2;
    mod(x * 2, l, mid, ql, qr, v);
    mod(x * 2 + 1, mid + 1, r, ql, qr, v);
    t[x] = t[x * 2] + t[x * 2 + 1];
    m[x] = max(m[2 * x], m[2 * x + 1]);
  }

  void set(int x, int l, int r, int ql, int qr, int v) {
    if (l > qr || r < ql)
      return;
    if (l == r) {
      t[x] = v;
      m[x] = t[x];
      return;
    }
    int mid = (l + r) / 2;
    set(x * 2, l, mid, ql, qr, v);
    set(x * 2 + 1, mid + 1, r, ql, qr, v);
    t[x] = t[2 * x] + t[2 * x + 1];
    m[x] = max(m[2 * x], m[2 * x + 1]);
  }

  ll query(int x, int l, int r, int ql, int qr) {
    if (l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return t[x];
    int mid = (l + r) / 2;
    return query(x * 2, l, mid, ql, qr) + query(x * 2 + 1, mid + 1, r, ql, qr);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m;
  cin >> n >> m;
  T t(n);

  while (m--) {
    int op, x, y, z;
    cin >> op >> x >> y;
    if (op == 0) {
      cout << t.query(1, 0, n-1, x, y) << '\n';
    } else if (op == 1) {
      t.set(1, 0, n-1, x, x, y);
    } else {
      cin >> z;
      t.mod(1, 0, n-1, x, y, z);
    }
  }
}
