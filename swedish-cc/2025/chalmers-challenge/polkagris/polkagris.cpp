#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using ll = long long;
#define int ll

using ld = long double;

using vi = vector<int>;
using vd = vector<ld>;

using pi = pair<int, int>;

using vpi = vector<pi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

ll euclid(ll a, ll b, ll &x, ll &y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}
template <int mod> struct Mint {
  ll x;
  Mint(ll xx) : x(xx) {
    x %= mod;
    x += mod;
    x %= mod;
  }
  // No-mod constructor
  Mint(ll xx, bool nope) : x(xx) {}
  Mint() : x(0) {}
  Mint operator+(Mint b) {
    int y = x + b.x;
    return {y - (y >= mod) * mod, false};
  }
  Mint operator-(Mint b) {
    int y = x - b.x;
    return {y + (y < 0) * mod, false};
  }
  Mint operator-() { return {-x + mod, false}; }
  Mint operator*(Mint b) { return {x * b.x % mod, false}; }
  Mint operator/(Mint b) { return {x * invert(b).x % mod, false}; }
  Mint invert(Mint a) {
    ll x, y, g = euclid(a.x, mod, x, y);
    assert(g == 1);
    return {(x + mod) % mod};
  }
  friend ostream &operator<<(ostream &out, const Mint &a) { return out << a.x; }
  friend istream &operator>>(istream &in, Mint &a) {
    ll val;
    in >> val;
    a = Mint(val);
    return in;
  }
};
typedef Mint<int(1e9 + 7)> Mod;

Mod p = 337;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, t;
  cin >> n >> t;

  string s, b;
  cin >> s >> b;

  vi pref, suff;

  {
    Mod lh, rh, ppow = 1;

    int start = 1;
    int len = 1;
    while (start + len < n) {
      dbg(start, len, lh, rh, ppow);

      lh = lh * p;
      lh = lh + s[start - 1];

      if (len > 1)
        rh = rh - s[start];
      rh = rh * p.invert(p);
      rh = rh + ppow * s[start + len];
      ppow = ppow * p;

      if (lh.x == rh.x) {
        pref.push_back(len);

        lh = 0;
        rh = 0;
        ppow = 1;
        // start = start + len + 1;
        start++;
        len = 1;
      } else {
        len++;
        start++;
      }
    }
  }

  reverse(all(s));

  {

    Mod lh, rh, ppow = 1;

    int split = 1;
    while (split <= n / 2) {
      lh = lh * p;
      lh = lh + s[split - 1];

      if (split > 1)
        rh = rh - s[split];
      rh = rh * p.invert(p);
      rh = rh + ppow * s[2 * split];
      ppow = ppow * p;

      if (lh.x == rh.x) {
        suff.push_back(split);

        lh = 0;
        rh = 0;
        ppow = 1;
      }

      split++;
    }
  }

  reverse(all(s));

  dbg(pref, suff);
}
