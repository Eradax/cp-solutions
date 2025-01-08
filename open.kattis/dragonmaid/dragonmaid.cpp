#include <bits/stdc++.h>

#ifdef DBG
#include "../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using pi = pair<int, int>;
using ti3 = tuple<int, int, int>;

using vi = vector<int>;
using vvi = vector<vi>;
using vpi = vector<pi>;
using vti3 = vector<ti3>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vti3 vp(n);
  rep(i, n) {
    int a, b;
    cin >> a >> b;
    vp[i] = {b, i, a};
  }

  int q;
  cin >> q;

  vti3 xk(q);
  vvi ans(q);

  rep(i, q) {
    int a, b;
    cin >> a >> b;
    xk[i] = {a, i, b};
  }

  sort(all(vp));
  sort(all(xk));

  dbg(vp, xk);

  int ip = 0;

  rep(i, q) {
    auto [x, ii, k] = xk[i];
    while (ip < n && get<0>(vp[ip]) <= x) {
      ans[ii].push_back(ip);
      ip++;
    }
  }

  dbg(ans);

  priority_queue<pi, vpi, greater<pi>> pq;
  priority_queue<pi, vpi, greater<pi>> pq2;

  vvi anss(q);

  rep(i, q) {
    dbg(pq);

    int ii = get<1>(xk[i]);

    rep(j, sz(ans[ii])) {
      int p = get<2>(vp[ans[ii][j]]);
      int iii = get<1>(vp[ans[ii][j]]);
      if (sz(pq) < 10) {
        pq.emplace(p, -iii);
      } else if (pq.top().first < p ||
                 (pq.top().first == p && -pq.top().second > iii)) {
        pq.pop();
        pq.emplace(p, -iii);
      }
    }

    pq2 = pq;

    dbg(pq2);

    int k = min(get<2>(xk[i]), sz(pq2)),
        rk = sz(pq2) - min(get<2>(xk[i]), sz(pq2));

    dbg(k);

    rep(_, rk) {
      dbg("pop");
      pq2.pop();
    }

    dbg(pq2);

    rep(_, k) {
      anss[ii].push_back(-pq2.top().second);
      pq2.pop();
    }
  }

  rep(i, q) {
    if (sz(anss[i])) {
      for (auto e : anss[i]) {
        cout << e + 1 << ' ';
      }
      cout << '\n';
    } else {
      cout << "-1\n";
    }
  }
}
