#include <bits/stdc++.h>

#ifdef DBG
  #include "../../../dbg.h"
#else
  #define dbg(...)
#endif

/*
links:
    https://open.kattis.com/problems/inverteddeck
source:
    Northwestern Europe Regional Contest (NWERC) 2019
*/

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define per(i, n) for (int i = n - 1; i >= 0; i--)

const int INF = 1e9;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> v(n);
  rep(i, n) {
    cin >> v[i];
  }

  vector<int> mins(n), maxs(n);

  maxs[0] = v[0];
  for (int i = 1; i < n; i++) {
    maxs[i] = max(v[i], maxs[i - 1]);
  }

  mins[n - 1] = v[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    mins[i] = min(v[i], mins[i + 1]);
  }

  dbg(mins, maxs);

  int start = 0;
  int end = 0;
  rep(i, n) {
    if (mins[i] == maxs[i])
      continue;
    start = i;
    break;
  }

  per(i, n) {
    if (mins[i] == maxs[i])
      continue;
    end = i;
    break;
  }

  dbg(start, end);

  reverse(v.begin() + start, v.begin() + end + 1);

  dbg(v);

  rep(i, n - 1) {
    if (v[i + 1] < v[i]) {
      cout << "impossible" << endl;
      return 0;
    }
  }

  cout << start + 1 << " " << end + 1 << endl;
}
