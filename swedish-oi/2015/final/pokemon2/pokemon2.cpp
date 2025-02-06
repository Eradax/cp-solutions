#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = (n) - 1; i >= 0; i--)

#define sz(c) (int)c.size()

const int INF = 1e9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(20);

  int n, m;
  cin >> n >> m;

  vector<vector<int>> p(n);
  vector<vector<int>> c(n);

  vector<long double> v(n, 0);

  rep(i, m) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    p[b].push_back(a);
    c[a].push_back(b);
  }

  v[0] = 1;

  rep(i, n) {
    sort(p[i].begin(), p[i].end(), [&](int l, int h) { return v[l] > v[h]; });

    long double f = 0.5;
    for (auto u : p[i]) {
      v[i] += f * v[u];
      f *= 0.5;
    }
  }

  // rep(i, n) {
  //     cout << v[i] << " ";
  // }
  // cout << endl;

  long double ans = 0;
  rep(i, n) {
    ans += v[i];
  }

  cout << ans * 100 << endl;
}
