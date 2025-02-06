#include <bits/stdc++.h>
using namespace std;

inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

const int len = 2 * (int)1e6 + 1;
bitset<len> dp;
bitset<len> created;

int main() {
  fast();

  dp[0] = 1;

  int n, t;
  cin >> n >> t;

  vector<int> vals(n);
  vector<short> mem(len);

  int block;
  for (int i = 0; i < n; i++) {
    cin >> block;
    vals[i] = block;
    created = (dp << block) & (~dp);
    dp |= dp << block;

    for (int j = created._Find_first(); j < len; j = created._Find_next(j)) {
      if (created[j] == 1) {
        mem[j] = i;
      }
    }
  }

  if (dp[t] == 0) {
    cout << "NO";
    return 0;
  }

  // Recreate the subset
  string ans(n, '0');
  while (t > 0) {
    int a = mem[t];
    t -= vals[a];
    ans[a] = '1';
  }

  cout << "YES\n";
  cout << ans;

  return 0;
}
