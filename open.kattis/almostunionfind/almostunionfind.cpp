#include <bits/stdc++.h>

#ifdef DBG
  #include "../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:
    Rujia Liu's Present 3: A datastructure contest celebrating the 100th
anniversary of Tsinghua University links:
    https://open.kattis.com/problems/almostunionfind
*/

using namespace std;

using ll = long long;

using vi = vector<int>;
using vvi = vector<vi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  while (cin >> n >> m) {
    vector<ll> sums(n);
    vector<unordered_set<int>> groups(n);
    vi group(n);

    rep(i, n) {
      sums[i] = i + 1;
      groups[i] = {i + 1};
      group[i] = i;
    }

    rep(_, m) {
      int t;
      cin >> t;

      if (t == 1) {
        int p, q;
        cin >> p >> q;
        p--;
        q--;

        int pg = group[p], qg = group[q];

        if (pg == qg)
          continue;

        if (sz(groups[pg]) > sz(groups[qg])) {
          swap(pg, qg);
        }

        for (auto e : groups[pg]) {
          groups[qg].insert(e);
          group[e - 1] = qg;
          sums[qg] += e;
        }

        groups[pg].clear();
        sums[pg] = 0;

      } else if (t == 2) {
        int p, q;
        cin >> p >> q;
        p--;
        q--;

        int pg = group[p], qg = group[q];

        if (pg == qg)
          continue;

        groups[pg].erase(p + 1);
        groups[qg].insert(p + 1);
        group[p] = qg;
        sums[pg] -= p + 1;
        sums[qg] += p + 1;
      } else {
        int p;
        cin >> p;
        p--;

        int pg = group[p];

        cout << sz(groups[pg]) << " " << sums[pg] << '\n';
      }
    }
  }
}
