#include <bits/stdc++.h>

#ifdef DBG
#include "../../../../dbg.h"
#else
#define dbg(...)
#endif

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define all(c) c.begin(), c.end()

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, m;
  cin >> n >> m;

  if (n == m) {
    cout << "Ja" << endl;
    return 0;
  }

  int i = 2;
  while (i * i <= n) {
    if (n % i != 0) {
      i++;
      continue;
    }

    if (2 * i + 2 * (n / i) - 4 == m) {
      cout << "Ja" << endl;
      return 0;
    }

    i++;
  }

  cout << "Nej" << endl;
}
