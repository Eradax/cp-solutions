#include <bits/stdc++.h>

#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;

using pi = pair<int, int>;
using vi = vector<int>;

const int INF = 1e9;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())

inline void pbif(vector<ll>* c, ll v) {
  dbg(v);

  if (abs(v) < INF)
    c->push_back(v);
}

struct MaT {
  int n;
  vector<pi> t;

  MaT(int n) : n(n), t(2 * n) {}

  pi comb(pi a, pi b) {
    dbg(a, b);

    pi res = {
        max(a.first, b.first),
        max(min(a.first, b.first), max(a.second, b.second))
    };

    dbg(res);

    return res;
  }

  void build() {
    for (int i = n - 1; i > 0; --i) {
      t[i] = comb(t[2 * i], t[2 * i + 1]);
    }
  }

  pi query(int l, int r) {
    pi res = {-INF, -INF};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res = comb(res, t[l++]);
      if (r & 1)
        res = comb(res, t[--r]);
    }
    return res;
  }
};

struct MiT {
  int n;
  vector<pi> t;

  MiT(int n) : n(n), t(2 * n) {}

  pi comb(pi a, pi b) {
    dbg(a, b);

    pi res = {
        min(a.first, b.first),
        min(max(a.first, b.first), min(a.second, b.second))
    };

    dbg(res);

    return res;
  }

  void build() {
    for (int i = n - 1; i > 0; --i) {
      t[i] = comb(t[2 * i], t[2 * i + 1]);
    }
  }

  pi query(int l, int r) {
    pi res = {INF, INF};
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1)
        res = comb(res, t[l++]);
      if (r & 1)
        res = comb(res, t[--r]);
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  MaT mat(n);
  MiT mit(n);

  // vi zc(n, 0);

  rep(i, n) {
    pi tmp;
    cin >> tmp.first;
    tmp.second = -INF;

    mat.t[n + i] = tmp;

    tmp.second *= -1;

    mit.t[n + i] = tmp;

    // zc[i] += tmp.first == 0;
  }

  // rep(i, n - 1) { zc[i + 1] += zc[i]; }

  mat.build();
  mit.build();

  rep(i, q) {
    int l, r;
    cin >> l >> r;
    l--;
    r--;

    ll ans = 1;
    ans *= mat.t[n + l].first;
    dbg(ans);
    ans *= mat.t[n + r].first;
    dbg(ans);

    vector<ll> vals;

    if (r - l + 1 < 6) {
      rep(i, r - l - 1) {
        pbif(&vals, mit.t[n + l + 1 + i].first);
      }
    } else {
      pbif(&vals, mat.query(l + 1, r).first);
      pbif(&vals, mat.query(l + 1, r).second);
      pbif(&vals, mit.query(l + 1, r).first);
      pbif(&vals, mit.query(l + 1, r).second);
    }

    dbg(vals);

    ll rans = -1e18;
    rep(i, sz(vals) - 1) {
      rep(j, sz(vals) - 1 - i) {
        rans = max(rans, ans * vals[i] * vals[i + j + 1]);
      }
    }

    // if (zc[r - 1] - zc[l + 1] > 0) {
    //   rans = max(rans, 0LL);
    // };

    cout << rans << '\n';
  }
}
