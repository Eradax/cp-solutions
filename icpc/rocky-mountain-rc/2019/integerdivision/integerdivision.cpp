#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
source:
    Rocky Mountain Regional Programming Contest 2019
links:
    https://open.kattis.com/problems/integerdivision
*/

using namespace std;

using ull = unsigned long long;

using vi = vector<int>;

#define rep(i, n) for (int i = 0; i < (n); i++)

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, d;
  cin >> n >> d;

  unordered_map<int, int> m;
  rep(i, n) {
    int tmp;
    cin >> tmp;

    m[tmp / d]++;
  }

  ull ans = 0;
  for (auto& e : m) {
    ans += ull(e.second) * (ull)(e.second - 1) / 2;
  }

  cout << ans << endl;
}
