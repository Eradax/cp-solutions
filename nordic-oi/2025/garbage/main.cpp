#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vl = vector<ll>;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

struct P {
  ll x, y, w;
};

struct T {
  int n, lh;
  vl t, d;

  T(int n) : n(n), lh(__bit_width(n)), t(2 * n), d(n) {}

  void apply(int p, ll v) {
    t[p] += v;
    if (p < n)
      d[p] += v;
  }

  void build(int p) {
    while (p > 1) {
      p /= 2;
      t[p] = max(t[2 * p], t[2 * p + 1]) + d[p];
    }
  }

  void push(int p) {
    for (int nl = lh; nl > 0; --nl) {
      int i = p >> nl;
      if (d[i] != 0) {
        apply(2 * i, d[i]);
        apply(2 * i + 1, d[i]);
        d[i] = 0;
      }
    }
  }

  void upd(int l, int r, ll v) {
    l += n, r += n;

    int nl = l, nr = r;
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1)
        apply(l++, v);
      if (r & 1)
        apply(--r, v);
    }

    build(nl);
    build(nr - 1);
  }

  ll query(int l, int r) {
    l += n;
    r += n;

    push(l);
    push(r - 1);

    ll res = 0;

    for (; l < r; l /= 2, r /= 2) {
      if (l & 1)
        res = max(res, t[l++]);
      if (r & 1)
        res = max(res, t[--r]);
    }

    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll w, h;
  cin >> n >> w >> h;

  vector<P> p(n);
  vl yp;
  rep(i, n) {
    cin >> p[i].x >> p[i].y >> p[i].w;
    yp.push_back(p[i].y);
  }

  sort(all(yp));
  yp.erase(unique(all(yp)), yp.end());

  rep(i, n) {
    p[i].y = lower_bound(all(yp), p[i].y) - yp.begin();
  }

  sort(all(p), [](P& a, P& b) { return a.x < b.x; });

  int ny = yp.size();

  vl r(ny);
  int j = 0;
  rep(i, ny) {
    while (j < ny && yp[j] < yp[i] + h)
      j++;
    r[i] = j - 1;
  }

  T t(ny);

  auto update_f = [&](int p, ll delta) {
    int L = lower_bound(all(r), p) - r.begin();
    if (L <= p)
      t.upd(L, p + 1, delta);
    else
      t.upd(p + 1, L - 1 + 1, -delta);
  };

  ll ans = 0;
  int rp = 0;
  rep(lp, n) {
    while (rp < n && p[rp].x < p[lp].x + w) {
      int pos = p[rp].y;
      update_f(pos, p[rp].w);
      rp++;
    }

    ans = max(ans, t.query(0, ny));

    int pos = p[lp].y;
    update_f(pos, -p[lp].w);
  }

  cout << ans << "\n";
}
