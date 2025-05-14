#include <bits/stdc++.h>
#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif
using namespace std;

using ll = long long;
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()
#define rep(i, l, h) for (int i = l; i < h; i++)
using vi = vector<int>;
using vl = vector<__int128_t>;

ostream& operator<<(ostream& o, __int128_t v) {
  if (v < 0) {
    o << '-';
    o << -v;
    return o;
  }
  if (v > 9) o << v / 10;
  o << (int)(v%10);
  return o;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vl a(n);
  vl b(m);

  for (int i = 0; i < n; i++) {
    ll v;
    cin >> v;
    a[i] = v;
  }

  for (int i = 0; i < m; i++) {
    ll v;
    cin >> v;
    b[i] = v;
  }

  vl c(n + m - 1);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      c[i + j] += a[i] * b[j];

  int nd = sz(c) - 1;
  while (nd && !c[nd])
    nd--;

  for (int i = 0; i <= nd; i++)
    cout << c[i] << ' ';
  cout << '\n';
}
