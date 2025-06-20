#include <bits/stdc++.h>
using namespace std;

// NOTE: To get 0.00 on kattis use faster io

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  while (n--) {
    int x;
    cin >> x;
    x *= 100;
    char t; cin >> t;
    int tt; cin >> tt;
    x += tt;

    int cnt = x*2 / 3;

    if (cnt * 3 / 2 == x || (cnt+1) * 3 / 2 == x) {
      cout << "VALID" << '\n';
    } else {
      cout << "IMPOSSIBLE" << '\n';
    }
  }
}
