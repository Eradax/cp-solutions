#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;
  while (n--) {
    double x;
    cin >> x;

    int cnt = floor(x / 0.015);
    if (floor(100 * 0.015 * cnt) / 100 == x ||
        floor(100 * 0.015 * (cnt + 1)) / 100 == x) {
      cout << "VALID" << '\n';
    } else {
      cout << "IMPOSSIBLE" << '\n';
    }
  }
}
