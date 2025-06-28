#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

// NOTE: use balzing-io for 0.02s on kattis 

#define uint32_t int

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
    uint32_t h = 0;
    for (auto j : s) {
      if ((j & ans) != ans)
        continue;
      j &= ((1u << i) - 1);
      j ^= 0xa729bf3e;
      j *= 0xd1cba227;
      h ^= j;
    }

    if (h == 0) {
      ans |= 1u << i;
    }
  }

  cout << ans + 1 << endl;
}
