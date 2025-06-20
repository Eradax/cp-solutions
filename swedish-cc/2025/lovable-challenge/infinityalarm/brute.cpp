#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<ll> s(n);
  for (auto& i : s) cin >> i;

  for (int i = 0;; i++) {
    int par = 0;
    for (auto j : s)
      par ^= ((j - 1) & i) == i;

    if (par) {
      cout << i + 1 << endl;
      break;
    }
  }
}
