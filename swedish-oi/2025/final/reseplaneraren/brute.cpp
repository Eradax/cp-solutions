#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

#define repp(i, s, n) for (int i = s; i < (n); i++)
#define rep(i, n) repp(i, 0, n)

using vi = vector<int>;
using vvi = vector<vi>;

using pi = pair<int, int>;
using vpi = vector<pi>;
using vvpi = vector<vpi>;

using bs = bitset<50000>;

using vbs = vector<bs>;

using ui = unordered_set<pi>;
using vui = vector<ui>;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, k, q;
  cin >> n >> k >> q;

  dbg(n, k, q);

  vvi adj(n);

  rep(i, n-1) {
    int u, v;
    cin >> u >> v;
    u--, v--;

    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  vbs sen(n);

  vpi trains(k);
  rep(i, k) {
    int s, t;
    cin >> s >> t;
    s--, t--;

    trains[i] = {s, t};

    sen[s].set(i);
    sen[t].set(i);
  }

  dbg(sen);

  vbs stops(n);

  function<bs(int, int)> dfs;
  dfs = [&](int u, int p) {
    dbg(u, p);
    bs curr = sen[u], curr2 = sen[u];

    for (auto v : adj[u]) {
      if (v == p)
        continue;

      bs tmp = dfs(v, u);
      curr ^= tmp;
      curr2 |= tmp;
    }

    stops[u] = curr2;

    return curr;
  };

  dfs(0, -1);

  dbg(stops);

  vi ans(q);
  rep(i, q) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;

    bs aa, bb, cc;
    aa = stops[a];
    bb = stops[b];

    cc = aa & bb;
    ans[i] = cc.any();

    dbg(a, b);
    dbg(aa, bb, cc);
  }

  rep(i, q) { cout << (ans[i] > 0 ? "Yes" : "No") << endl; }
}
