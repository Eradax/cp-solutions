#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, l, n) for (int i = l; i < (n); i++)

constexpr ll MOD = 1e9 + 7;
constexpr int MAXN = 2e5 + 10;

const auto inv{[]() {
  array<ll, MAXN> res{};
  rep(i, MAXN) {
    if (i < 2) {
      res[i] = 1;
    } else {
      res[i] = (res[MOD % i] * (MOD - MOD / i)) % MOD;
    }
  }
  return res;
}()};

ll euclid(ll a, ll b, ll& x, ll& y) {
  if (!b)
    return x = 1, y = 0, a;
  ll d = euclid(b, a % b, y, x);
  return y -= a / b * x, d;
}
template <int mod>
struct Mint {
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
  Mint invert(Mint a) { return inv[a.x]; }
  friend ostream& operator<<(ostream& out, const Mint& a) { return out << a.x; }
  friend istream& operator>>(istream& in, Mint& a) {
    ll val;
    in >> val;
    a = Mint(val);
    return in;
  }
};
typedef Mint<int(1e9 + 7)> Mod;

Mod binpow(Mod a, Mod b) {
  Mod ret = 1;
  Mod e = a;
  while (b.x) {
    if (b.x % 2)
      ret = ret * e;
    e = e * e;
    b.x >>= 1;
  }

  return ret;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  Mod n, k, s, a;
  cin >> n >> k >> s >> a;

  int mi = n.x < k.x ? n.x : k.x;
  int ma = n.x > k.x ? n.x : k.x;

  dbg(mi, ma);

  Mod ans(0, 0);

  Mod stub(1, 0);
  Mod kbit(binpow(k, n + 2));
  Mod kibit(binpow(k - 1, n + 1) * (k + 1));

  Mod kfac(1, 0), nfac(1, 0);

  repp(i, 1, ma + 1) {
    if (i <= n.x)
      nfac = nfac * i;
    if (i <= k.x)
      kfac = kfac * i;

    if (i <= n.x + 1)
      stub = stub * inv[i];
    if (i <= k.x + 1)
      stub = stub * inv[i];
  }

  dbg(kfac, nfac);
  dbg(stub, kbit, kibit);

  if (a.x) {
    rep(i, mi + 1) {
      stub = stub * inv[i] * inv[i] * (n - i) * (k - i);
      kbit = kbit * inv[k.x];
      kibit = kibit * (k - i) * inv[k.x - 1] * inv[k.x - i + 1];

      ans = ans + stub * (kbit - kibit);

      dbg(stub, kbit, kibit);
      dbg(ans);
    }

    ans = ans * binpow(a, n) * nfac * kfac * inv[k.x];
  } else {
    // FIX: This is wrong, see notes

    int i = n.x;

    stub = stub * inv[i] * inv[i] * inv[n.x - i] * inv[n.x - i];
    kbit = kbit * inv[k.x];
    kibit = kibit * (k - i) * inv[k.x - 1] * inv[k.x - i + 1];

    ans = ans + stub * (kbit - kibit);

    dbg(ans);
  }

  cout << ans << endl;
}
