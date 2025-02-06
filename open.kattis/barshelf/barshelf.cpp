#include <bits/stdc++.h>

using namespace std;

using ll = long long;

using pi = pair<int, int>;

using vi = vector<int>;
using vpi = vector<pi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)
#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

struct T {
  vi t;
  T(int n) : t(n + 1) {}

  void upd(int i) {
    for (i++; i < sz(t); i += i & -i) {
      t[i]++;
    }
  }

  int query(int r) {
    if (r < 0)
      return 0;
    if (r >= sz(t))
      r = sz(t) - 1;

    int ret = 0;
    for (r++; r > 0; r -= r & -r) {
      ret += t[r];
    }
    return ret;
  }

  int query(int l, int r) {
    int ret = 0;
    ret += query(r);
    ret -= query(l - 1);
    return ret;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio();

  int n;
  cin >> n;

  vpi v(n);
  rep(i, n) {
    cin >> v[i].first;
    v[i].second = i;
  }

  sort(all(v));

  vi le(n), ge(n);

  {
    T t(n);
    int id = 0;
    rep(i, n) {
      int g = v[i].first / 2;
      while (id < n) {
        if (v[id].first > g)
          break;
        t.upd(v[id].second);
        id++;
      }

      le[v[i].second] = t.query(v[i].second + 1, n - 1);
    }
  }

  {
    T t(n);
    int id = n - 1;
    per(i, n) {
      int g = v[i].first * 2;
      while (id >= 0) {
        if (v[id].first < g)
          break;
        t.upd(v[id].second);
        id--;
      }

      ge[v[i].second] = t.query(0, v[i].second - 1);
    }
  }

  ll ans = 0;
  rep(i, n) {
    ans += (ll)le[i] * (ll)ge[i];
  }

  cout << ans << endl;
}
