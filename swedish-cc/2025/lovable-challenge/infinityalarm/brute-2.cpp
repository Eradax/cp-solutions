#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  int tot = 0;
  vector<int> s(n);
  for (auto& i : s) {
    cin >> i;
    i--;

    tot |= i;
  }

  for (int i = tot, i2 = 0; i >= 0; i = (i - 1) & tot, i2 = i ^ tot)  {
    int par = 0;
    for (auto j : s)
      par ^= (j & i2) == i2;

    if (par) {
      cout << i2 + 1 << '\n';
      break;
    }
  }
}
