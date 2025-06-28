#include <bits/stdc++.h>
using namespace std;

#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, a;
  cin >> n >> a;

  vector<int> b(n);
  for (auto& i : b) cin >> i;

  set<pair<int, int>> keys;

  for (auto y : b) {
    int x = 0;
    while (y % a == 0) {
      y /= a;
      x++;

      keys.emplace(x, y);
    }
  }

  cout << sz(keys) << endl;
}
