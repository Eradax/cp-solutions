#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ui = unsigned int;

ui r2(ui v, int a) {
  return ((v >> a) | (v << (20 - a))) & 0xfffff;
}

ll tra(ll msg) {
  msg &= 0xffffffffff;
  
  ui a = msg & 0xfffff;
  a = r2(a, 6);
  a ^= 0xc21f3;
  a |= 0xaaaaa;

  ui b = (msg >> 20) & 0xfffff;
  b ^= a;
  b |= 0xaaaaa;
  b ^= 0xbf83f;
  b = r2(b, 6);

  a ^= b;

  return (ll(a) << 20) | b;
}

ll inv(ll t) {
  ui a3 = (t >> 20) & 0xfffff;
  ui b4 = t & 0xfffff;

  ui b3 = r2(b4, 20 - 6);
  ui b2 = b3 ^ 0xbf83f;

  ui a2 = a3 ^ b4;

  for (ui cand = 0; cand < (1u << 20); cand++) {
    ui a1 = r2(cand, 6) ^ 0xc21f3;
    if ((a1 | 0xaaaaa) != a2)
      continue;

    ui mask = 0x55555;
    ui b0 = ((b2 & mask) ^ (a2 & mask)) | (a2 & 0xaaaaa);

    ll x = (ll(b0) << 20) | cand;
    if (tra(x) == t)
      return x;
  }

  return -1;
}

int main() {
  ll t;
  cin >> t;
  cout << inv(t);
}
