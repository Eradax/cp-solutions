#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define repp(i, s, n) for (int i = s; i < (n); i++)
#define all(c) c.begin(), c.end()

int main() {
  cin.tie(0)->sync_with_stdio(0);
  int n, m, g;
  cin >> n >> m >> g;

  if (n < m) swap(n, m);

  vi gg(g);
  rep(i, g) { cin >> gg[i]; }

  sort(all(gg));

  vi count(g);

  rep(i, n) {
    int cost = min(i + 1, m);
    count[i % g] += cost;
  }

  repp(i, 1, m) {
    int cost = m - i;
    count[(n + i - 1) % g] += cost;
  }

  sort(all(count));

  bool poss = 1;

  rep(i, g) {
    poss &= count[i] <= gg[i];
  }

  cout << (poss ? "Ja" : "Nej") << endl;
}
