#include <bits/stdc++.h>
using namespace std;

// #ifdef DBG
// #define dbg(expr) cerr <<

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    int tot = 0;
    for (int i = 0; i < n; i++) {
      tot += abs((n - i) - (i+1));
    }

    cout << tot / 2 + 1 << '\n';
  }
}
