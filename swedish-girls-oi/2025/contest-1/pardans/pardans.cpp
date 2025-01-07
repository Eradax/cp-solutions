#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, d;
  cin >> n >> d;

  vi l(2 * n);
  rep(i, 2 * n) { cin >> l[i]; }

  sort(all(l));

  rep(i, n) {
    if (l[n + i] - l[i] < d) {
      cout << "Nej" << endl;
      return 0;
    }
  }

  cout << "Ja" << "\n";
  rep(i, n) { cout << l[n + i] << " " << l[i] << '\n'; }
}
