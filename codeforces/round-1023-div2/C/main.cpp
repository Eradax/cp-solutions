#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    ll k;
    cin >> n >> k;

    vi s(n);
    vl a(n);

    string str;
    cin >> str;
    for (int i = 0; i < n; i++) {
      s[i] = str[i] == '1';
    }

    for (int i = 0; i < n; i++) {
      cin >> a[i];
      if (s[i] == 0)
        a[i] = -1e18;
    }

    ll ma = a[0];
    ll me = a[0];

    for (int i = 1; i < n; i++) {
      me = max<ll>(me + a[i], a[i]);
      me = max<ll>(me, -1e18);
      me = min<ll>(me, 1e18);
      ma = max(ma, me);
    }

    if (ma == k) {
      cout << "Yes" << '\n';
      for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
      cout << '\n';

      continue;
    }

    bool f = 1;
    for (int idx = 0; idx < n; idx++) {
      if (s[idx])
        continue;

      // cout << "Idx: " << idx << endl;

      ll lo = -1e18 - 1;
      ll hi = 1e18 + 10;

      while (lo + 1 < hi) {
        ll mi = lo + (hi - lo) / 2;

        a[idx] = mi;

        ll ma = a[0];
        ll me = a[0];

        for (int i = 1; i < n; i++) {
          me = max<ll>(me + a[i], a[i]);
          me = max<ll>(me, -1e18);
          me = min<ll>(me, 1e18);
          ma = max(ma, me);
        }

        if (ma >= k) {
          hi = mi;
        } else {
          lo = mi;
        }
      }

      a[idx] = hi;
      ll ma = a[0];
      ll me = a[0];

      for (int i = 1; i < n; i++) {
        me = max<ll>(me + a[i], a[i]);
        me = max<ll>(me, -1e18);
        me = min<ll>(me, 1e18);
        ma = max(ma, me);
      }

      if (abs(hi) <= 1e18 && ma == k) {
        cout << "Yes" << '\n';
        for (int i = 0; i < n; i++) {
          cout << a[i] << ' ';
        }
        cout << '\n';

        f = 0;
        break;
      }

      a[idx] = -1e18;
      break;
    }
    if (f)
      cout << "No" << '\n';
  }
}
