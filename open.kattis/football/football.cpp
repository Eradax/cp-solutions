#include <bits/stdc++.h>

#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif

#define gc() getchar_unlocked()
template <typename T>
inline void read(T& v) {
  v = 0;
  char c;
  while ((c = gc()) && c != ' ' && c != '\n') {
    v *= 10;
    v += c - '0';
  }
}

#define rint(a) read(a)
// #define rint(a) cin >> a

using namespace std;

using ll = long long;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  rint(n);
  rint(m);

  vector<ll> a(n);

  rep(i, m) {
    rep(j, n / 2) {
      int t;
      rint(t);

      dbg(t);

      t--;

      a[t] |= (1LL << i);
    }

    while (getchar_unlocked() != '\n') {
    }
  }

  dbg(a);

  sort(all(a));
  int d = sz(a) > 0;
  rep(i, sz(a) - 1) {
    d += a[i] != a[i + 1];
  }

  dbg(d);

  cout << (d == n ? "YES" : "NO") << endl;
}
