#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

// NOTE: use balzing-io for 0.02s on kattis

#define sz(c) ((int)c.size())

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
    int h[8] = {0};
    int k = 0;
    for (; k + 8 <= sz(s); k += 8)
    {
      // for good measure
      #pragma GCC ivdep
      for (int j =0;j<8;j++)
      {
        int v = s[k + j];
        v &= ((1u << i) - 1);
        v ^= 0xa729bf3e;
        v *= 0xd1cba227;
        h[j] ^= v;
      }
    }
    int res = 0;
    for (auto x : h) res ^=x;
    while (k<sz(s))
    {
      int j = s[k];
      j &= ((1u << i) - 1);
      j ^= 0xa729bf3e;
      j *= 0xd1cba227;
      res ^= j;
      k++;
    }

    if (res == 0) {
      ans |= 1u << i;

      s.erase(remove_if(s.begin(), s.end(), [&](const auto& j){
        return ((j >> i) & 1) ^ 1;
      }), s.end());
    }
  }

  cout << ans + 1 << endl;
}
