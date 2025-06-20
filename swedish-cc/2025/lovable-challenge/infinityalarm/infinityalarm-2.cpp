#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<uint32_t> s(n);
  for (auto& i : s) {
    cin >> i;
    i--;
  }

  uint32_t ans = 0;
  for (int i = 31; i >= 0; i--) {
    bitset<(int)1e9> bs;
    for (auto j : s)
      bs.flip(j & ((1u << i) - 1));

    if (bs.none()) {
      ans |= 1u << i;

      s.erase(remove_if(s.begin(), s.end(), [&](const auto& j){
        return ((j >> i) & 1) ^ 1;
      }), s.end());
    }
  }

  cout << ans + 1 << endl;
}
