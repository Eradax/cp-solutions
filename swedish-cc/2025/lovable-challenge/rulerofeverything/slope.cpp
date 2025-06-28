#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

// NOTE: use blazing-io for 0.04s on kattis

#define sz(c) ((int)c.size())

#define fi first
#define se second

using ll = long long;
using vl = vector<ll>;
using pl = pair<ll, ll>;
using vpl = vector<pl>;

const ll MAX = 8e9 + 1;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;
  
  vpl p(n);
  for (auto& [a, b] : p)
    cin >> a >> b;

  sort(p.begin(), p.end(), [](pl l, pl r) {
    return (l.fi > 1 || r.fi > 1) ? (l.fi - 1) * r.se < (r.fi - 1) * l.se : l.se > r.se;
  });

  vl vals = {0};
  for (auto [a, b] : p) {
    vals.push_back(a * vals.back() + b);
    
    if (a > 1)
      for (int i = sz(vals) - 2; i > 0; i--)
        vals[i] = max(vals[i], a * vals[i - 1] + b);

    while (sz(vals) > 2 && vals[sz(vals) - 2] >= MAX)
      vals.pop_back();
  }

  for (int i = 0; i < q; i++) {
    ll k;
    cin >> k;

    int ans = distance(vals.begin(), lower_bound(vals.begin(), vals.end(), k));
    cout << (ans < sz(vals) ? ans : -1) << ' ';
  }
  cout << endl;
}
