#include <bits/stdc++.h>
#include <ext/rope>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  __gnu_cxx::rope<int> r;

  int q;
  cin >> q;
  while (q--) {
    int t, x, y;
    cin >> t >> x;
    if (t == 0) {
      cin >> y;
      r.insert(x, __gnu_cxx::rope<int>{y});
    } else if (t == 1) {
      r.erase(x, 1);
    } else if (t == 2) {
      cout << r[x] << '\n';
    }
  }
}
