#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int r;
  cin >> r;

  vector<vector<pair<int, int>>> a(r * r);

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < r; j++) {
      int v;
      cin >> v;
      a[v].emplace_back(i, j);
    }
  }

  for (int i = 0; i < r * r - 1; i++) {
    for (int j = 0; j < sz(a[i]) - 1; j++) {
      if (a[i][j].second <= a[i][j + 1].second) {
        cout << 0;
        return 0;
      }
    }
  }

  cout << 1 << endl;
}
