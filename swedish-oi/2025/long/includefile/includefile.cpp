#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using vi = vector<int>;

using ll = long long;
using vl = vector<ll>;

using vs = vector<string>;

static const ll CAP = 1e12;

ll cpow(ll b, int e) {
  ll ans = 1;
  while (e) {
    if (b >= CAP)
      return CAP;
    if (e & 1) {
      if (ans > CAP / b)
        return CAP;
      ans *= b;
    }
    e >>= 1;
    if (e) {
      if (b > CAP / b) {
        b = CAP;
      } else {
        b *= b;
      }
    }
  }
  return ans;
};

int compEff(int n, int r, int k) {
  if (r == 0)
    return 0;
  if (r == 1) {
    int m0 = ceil((CAP - n) / double(n - 1));
    return min(k, m0);
  }
  double A = (double)r * (n - 1) / (r - 1);
  double B = double(n - r) / (r - 1);
  double threshold = (CAP + B) / A;
  int m0 = ceil(log(threshold) / log(r));
  return min(k, m0) + 10;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k, q;
  cin >> n >> k >> q;
  cin.ignore();

  int a = 0;

  vi isInc(n), prefInc(n + 1);
  vs lines(n);
  for (auto& i : lines)
    getline(cin, i);

  for (int i = 0; i < n; i++) {
    isInc[i] = lines[i] == "#include \"main.hpp\"";
    prefInc[i + 1] = isInc[i] + prefInc[i];
    if (!prefInc[i + 1])
      a++;
  }

  auto getTotLines = [&](int m) -> ll {
    if (!m || !prefInc[n])
      return n;
    if (prefInc[n] == 1) {
      ll ans = n;
      ans += (ll)m * (n - 1);
      return min(ans, CAP);
    }

    ll r = prefInc[n];
    ll rp = cpow(r, m);
    if (rp >= CAP)
      return CAP;
    ll num = rp - 1;
    __int128 p2 = (__int128)(n - r) * num;
    p2 /= r - 1;
    __int128 ans = (__int128)rp * n + p2;
    return ans >= CAP ? CAP : (ll)ans;
  };

  auto solve = [&](ll l, int m) -> ll {
    if (m == 0)
      return l;
    if (l < a)
      return l;

    {
      int lo = 1;
      int hi = m;
      while (lo < hi) {
        int mi = lo + (hi - lo) / 2;
        ll t = getTotLines(mi - 1);
        // dbg(lo, hi, mi, t);
        if (l - a < t)
          hi = mi;
        else
          lo = mi + 1;
      }

      dbg(lo, m, l);

      int diff = m - lo;
      m = lo;
      l -= (ll)diff * a;
      if (l < 0)
        l %= a;
      if (l < 0)
        l += a;
    }

    while (m) {
      ll cost = getTotLines(m - 1);

      int lo = 0;
      int hi = n - 1;
      while (lo < hi) {
        int mi = lo + (hi - lo) / 2;

        ll pref = (ll)mi + (cost - 1) * prefInc[mi + 1];
        if (pref >= l)
          hi = mi;
        else
          lo = mi + 1;
      }

      if (!isInc[lo])
        return lo;

      // dbg(l, lo, cost, m, prefInc);

      l -= (ll)lo + (cost - 1) * prefInc[lo];

      m--;
    }

    dbg(l);

    return l;
  };

  dbg(a);

  if (prefInc[n] == 0) {
    for (int i = 0; i < q; i++) {
      ll a;
      cin >> a;
      a--;
      cout << lines[a] << '\n';
    }
  } else if (prefInc[n] == 1) {
    for (int i = 0; i < q; i++) {
      ll li;
      cin >> li;
      li--;

      if (li < (__int128)(k+1) * a) {
        li %= a;
      } else if (li == (__int128)(k+1) * a) {
        li = a;
      } else {
        li = a + 1 + (li - (__int128)(k+1) * a - 1) % (n - a - 1);
      }

      cout << lines[li] << '\n';
    }
  } else {
    for (int i = 0; i < q; i++) {
      ll a;
      cin >> a;
      a--;
      dbg(a);
      cout << lines[solve(a, k)] << '\n';
    }
  }
}
