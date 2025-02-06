#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int knapsack(vi w, int t) {
  int a = 0, b = 0, x;
  while (b < sz(w) && a + w[b] <= t)
    a += w[b++];
  if (b == sz(w))
    return a;
  int m = *max_element(all(w));
  vi u, v(2 * m, -1);
  v[a + m - t] = b;
  rep(i, b, sz(w)) {
    u = v;
    rep(x, 0, m) v[x + w[i]] = max(v[x + w[i]], u[x]);
    for (x = 2 * m; --x > m;)
      rep(j, max(0, u[x]), v[x]) v[x - w[j]] = max(v[x - w[j]], j);
  }
  for (a = t; v[a + m - t] < 0; a--)
    ;
  return a;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, t;
  cin >> n >> t;
  vi vals(n);
  rep(i, 0, n) cin >> vals[i];

  cout << knapsack(vals, t);
}
