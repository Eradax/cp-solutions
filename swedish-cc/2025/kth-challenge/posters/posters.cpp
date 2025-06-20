#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int p, h, t;
  cin >> p >> h >> t;

  cout << max(0, (t - p - h) / max(p, h) + (t - p - h >= 0)) << '\n';
}
