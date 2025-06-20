#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int r;
  cin >> r;

  vector<array<int, 3>> a;

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < r; j++) {
      int v;
      cin >> v;
      a.push_back({v, i, j});
    }
  }

  sort(a.begin(), a.end());

  for (int i = 0; i < r * r - 1; i++) {
    if (a[i][0] == a[i+1][0] && a[i][2] <= a[i+1][2]) {
      cout << 0 << endl;
      return 0;
    }
  }

  cout << 1 << endl;
}
