// #pragma GCC optimize("Ofast")
// #include <bitset>
// #pragma GCC target("avx2")
#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < n; i++)
#define rep(i, n) repp(i, 0, n)

#define perr(i, s, n) for (int i = n - 1; i >= s; i--)
#define per(i, n) perr(i, 0, n)

#define all(c) c.begin(), c.end()
#define sz(c) ((int)c.size())

using ll = long long;
#define int ll

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

static constexpr int INF = 1e18;

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m, t;
  cin >> n >> m >> t;

  vvpi adj(n);
  vi par(n);

  rep(_, n - 1) {
    int a, b, ti;
    cin >> a >> b >> ti;
    adj[a].emplace_back(b, ti);
    adj[b].emplace_back(a, ti);
  }

  {
    function<void(int, int)> dfs = [&](int u, int p) {
      par[u] = p;

      for (auto [v, _] : adj[u]) {
        if (v == p)
          continue;
        dfs(v, u);
      }
    };
    dfs(0, -1);
  }

  vi energy(n);
  energy[0] = INF;
  repp(i, 1, n) cin >> energy[i];

  vi rats(m);
  vi ratsat(n, -1);
  rep(i, m) {
    cin >> rats[i];
    ratsat[rats[i]] = i;
  }

  dbg(adj);
  dbg(par);

  function<tuple<map<int,int>, int, int>(int)> dfs = [&](int u) -> tuple<map<int, int>, int, int> {
    tuple<map<int, int>, int, int> curr;

    if (ratsat[u] != -1) {
      get<0>(curr)[0] = energy[u];
      get<2>(curr) = energy[u];

      // dbg(curr);

      return curr;
    } else {
      // curr.first[0] = 0;
    }

    // dbg(u, curr);

    for (auto [v, w] : adj[u]) {
      if (v == par[u])
        continue;

      tuple<map<int, int>, int, int> tmp = dfs(v);
      get<1>(tmp) += w;

      // dbg(u, v, curr, tmp);
      if (sz(get<0>(tmp)) > sz(get<0>(curr))) {
        swap(tmp, curr);
      }
      // dbg(curr, tmp);

      for (auto [x, y] : get<0>(tmp)) {
        if (x + get<1>(tmp) - get<1>(curr) >= t || y == 0) continue;
        get<0>(curr)[x + get<1>(tmp) - get<1>(curr)] += y;
        get<2>(curr) += y;
      }

      // get<2>(curr) += get<2>(tmp);
    }

    // dbg(u, curr);

    int& tot = get<2>(curr);
    auto it = get<0>(curr).end();
    if (it == get<0>(curr).begin()) {
      return curr;
    }

    it--;


    dbg(tot, curr);

    while (it != get<0>(curr).begin() && tot > energy[u]) {
      tot -= (*it).second;
      dbg((*it));
      if (tot < energy[u]) {
        (*it).second = energy[u] - tot;
        tot += (*it).second;

        assert(tot == energy[u]);
      } else {
        it = get<0>(curr).erase(it);
        it--;
      }
    }

    dbg(tot, curr);

    if (tot > energy[u]) {
      tot -= (*it).second;
      if (tot < energy[u]) {
        (*it).second = energy[u] - tot;
        tot += (*it).second;

        assert(tot == energy[u]);
      } else {
        it = get<0>(curr).erase(it);

        // dbg(energy[u], tot);

        assert(0);
      }
    }

    dbg("------", u, curr, tot, "----------");
    // dbg("res: ", curr);

    return curr;
  };

  tuple<map<int, int>, int, int> res = dfs(0);

  dbg(res);

  int ans = 0;
  int slope = 0;
  for (auto it = get<0>(res).begin(); it != get<0>(res).end(); it++) {
    auto nxt = next(it);

    if ((*it).first + get<1>(res) >= t) break;

    slope += (*it).second;

    int tmp = slope;



    dbg((*it), slope);
    dbg(ans);

    if (nxt == get<0>(res).end()) {
      tmp *= max(t - (*it).first - get<1>(res), 0LL);

      dbg(t, (*it), tmp);
    } else {
      tmp *= min((*nxt).first + get<1>(res), t) - (*it).first - get<1>(res);

      dbg((*nxt), (*it), tmp);
    }

    ans += tmp;
  }

  cout << ans << endl;
}
