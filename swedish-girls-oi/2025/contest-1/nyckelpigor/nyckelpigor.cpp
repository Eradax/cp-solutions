#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using pii = pair<int, int>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()

int main() {
  int x, n;
  cin >> x >> n;

  vector<pii> vh(n);

  rep(i, n) { cin >> vh[i].first >> vh[i].second; }

  sort(all(vh), [](pii a, pii b) {
    return abs(a.first - a.second) < abs(b.first - b.second);
  });

  int ans = 0;
  rep(i, n) {
    int cost = abs(vh[i].first - vh[i].second);
    if (x < cost) {
      break;
    }
    x -= cost;
    ans++;
  }

  cout << ans << endl;
}
