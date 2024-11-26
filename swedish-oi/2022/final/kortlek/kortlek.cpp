#include <bits/stdc++.h>
// #include "../../../../dbg.h"
#define dbg(...)

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;

  cin >> n >> m;

  vector<long long> a(n), b(m);

  rep(i, n) cin >> a[i];
  rep(i, m) cin >> b[i];

  vector<long long> pre1(n);
  vector<long long> pre2(n);

  sort(a.begin(), a.end());
  sort(b.begin(), b.end());

  long long c1, c2;
  c1 = c2 = 0;
  rep(i, n) {
    pre1[i] = c1 += abs(a[i] - b[i]);
    pre2[i] = c2 += abs(a[i] - b[i + 1]);
  }

  dbg(a);
  dbg(b);
  dbg(pre1);
  dbg(pre2);

  if (n == m) {
    cout << pre1[n - 1] << endl;
    return 0;
  }

  long long ans = 1e18;
  rep(i, m) {
    long long tmp1 = 0;
    tmp1 += (i - 1 >= 0 ? pre1[i - 1] : 0);
    tmp1 += pre2[n - 1] - (i - 1 >= 0 ? pre2[i - 1] : 0);

    ans = min(ans, tmp1);
  }

  cout << ans << endl;
}
