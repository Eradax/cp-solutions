#include <bits/stdc++.h>
using namespace std;

const int B = 31;

#define sz(c) ((int)c.size())

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n;
  cin >> n;

  vector<uint32_t> s(n);
  vector<uint32_t> ns;
  for (auto& i : s) {
    cin >> i;
    i--;
  }

  unordered_map<uint32_t, int> cntr;
  int ans = 0;
  for (int i = B; i >= 0; i--) {
    cntr.clear();
    ns.clear();
    for (auto j : s)
      cntr[j & ((1 << i) - 1)] ^= 1;

    for (auto [v, c] : cntr)
      if (c)
        ns.push_back(v);

    if (sz(ns))
      s = ns;
    else {
      ans += 1 << i;
      ns.clear();
      for (auto j : s)
        if (j & (1 << i))
          ns.push_back(j);

      s = ns;
    }
  }

  cout << ans + 1 << endl;
}
