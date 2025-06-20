#include <bits/stdc++.h>
using namespace std;

#define fi first
#define se second

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    int s = 0;
    int t = 0;

    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      y += x;

      s ^= x;
      t ^= y;
    }

    t -= s;

    cout << s << " " << t << '\n';
  }
}
