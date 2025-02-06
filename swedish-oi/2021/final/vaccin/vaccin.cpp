#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<int> pre(n);

  rep(i, n) {
    cin >> pre[i];
    if (i)
      pre[i] += pre[i - 1];
  }

  dbg(pre);

  vector<pair<int, int>> ppl(q);
  rep(i, q) {
    cin >> ppl[i].first;
    ppl[i].second = i;
  }

  dbg(ppl);

  sort(ppl.begin(), ppl.end());

  dbg(ppl);

  vector<int> ans(q, -1);

  int qp = 0;
  int np = 0;
  while (qp < q && np < n) {
    if (ppl[qp].first < pre[np]) {
      ans[ppl[qp++].second] = 1 + np;
    } else {
      np++;
    }
  }

  rep(i, q) {
    cout << ans[i] << '\n';
  }
}
