#include <bits/stdc++.h>
using namespace std;

inline void fast() {
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
}

bitset<(int)1e7> dp;
map<int, int> nums;

int main() {
  fast();

  dp[0] = 1;

  int n;
  cin >> n;

  int block;

  for (int i = 0; i < n; i++) {
    cin >> block;
    nums[block] += 1;
  }

  for (auto& i : nums) {
    while (i.second >= 3) {
      i.second -= 2;
      nums[2 * i.first]++;
    }
  }

  for (auto& i : nums) {
    for (int j = 1; j <= i.second; j++) {
      dp |= dp << (i.first);
    }
  }

  cout << dp.count();

  return 0;
}
