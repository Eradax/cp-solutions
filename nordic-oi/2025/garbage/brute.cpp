#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vl = vector<ll>;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define all(c) c.begin(), c.end()

struct P {
  ll x, y, w;
};

struct T {
  int n;
  vl e;
  T(int n) : n(n), e(n + 1) {}

  void upd(int i, ll v) {
    i++;
    for (; i <= n; i += i & -i)
      e[i] += v;
  }

  ll q(int i) {
    i++;
    ll ret = 0;
    for (; i > 0; i -= i & -i)
      ret += e[i];
    return ret;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  ll w, h;
  cin >> n >> w >> h;

  vector<P> p(n);
  vl yp;
  rep(i, n) {
    cin >> p[i].x >> p[i].y >> p[i].w;
    yp.push_back(p[i].y);
  }

  sort(all(yp));
  yp.erase(unique(all(yp)), yp.end());

  rep(i, n) {
    p[i].y = lower_bound(all(yp), p[i].y) - yp.begin();
  }

  sort(all(p), [](P& a, P& b) { return a.x < b.x; });

  int ny = yp.size();

  vl r(ny);
  int j = 0;
  rep(i, ny) {
    while (j < ny && yp[j] < yp[i] + h)
      j++;
    r[i] = j - 1;
  }

  T t(ny);

  ll ans = 0;
  int rp = 0;
  rep(l, n) {
    while (rp < n && p[rp].x < p[l].x + w) {
      int pos = p[rp].y;
      t.upd(pos, p[rp].w);
      rp++;
    }

    ll curr = 0;
    rep(i, ny) {
      ll tmp = t.q(r[i]);
      tmp -= i == 0 ? 0 : t.q(i - 1);
      curr = max(curr, tmp);
    }

    ans = max(ans, curr);

    int pos = p[l].y;
    t.upd(pos, -p[l].w);
  }

  cout << ans << endl;
}
