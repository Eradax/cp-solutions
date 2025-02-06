#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

using ll = long long;
#define int ll

using ld = long double;

using vi = vector<int>;
using vd = vector<ld>;

using pi = pair<int, int>;

using vpi = vector<pi>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define sz(c) ((int)c.size())
#define all(c) c.begin(), c.end()

signed main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  vpi ppl;

  int tot = 0;

  rep(i, n) {
    string name;
    int d;
    cin >> name >> d;

    if (name == "Joshua" || name == "Gustav") {
      ppl.emplace_back(d, 2);
      tot += 2;
    } else {
      ppl.emplace_back(d, 1);
      tot += 1;
    }
  }

  sort(all(ppl));

  vpi intervals;
  rep(i, m) {
    int l, r;
    cin >> l >> r;

    intervals.emplace_back(l, r);
  }

  sort(all(intervals));

  dbg(intervals, ppl);

  int ans = 0;
  int pplp = 0;
  int intvlp = 0;

  while (pplp < n && intvlp < m) {
    if (intervals[intvlp].first > ppl[pplp].first) {
      pplp++;
    } else if (ppl[pplp].first <= intervals[intvlp].second) {
      dbg(pplp);

      ans += ppl[pplp].second;
      pplp++;

    } else {
      intvlp++;
    }
  }

  cout << tot - ans << endl;
}
